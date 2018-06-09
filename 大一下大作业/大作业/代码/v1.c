#include <iostream>

using namespace std;

enum Plane_status{null, arriving, departing};
enum Error_code {fail, success}

class Plane{
public:
   Plane();
   Plane(int flt, int time, Plane_status status);
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;
private:
   int flt_num;
   int clock_start;
   Plane_status state;
};

enum Runway_activity {idle, land, takeoff}
class Runway
{
    public:
       Runway(int limit);
       Error_code can_land(const Plane& current);
       Error_code can_depart(const Plane& current);
       Runway_activity activity(int time, Plane &moving);
       void shut_down(int time) const;
    private:
       Extended_queue landing;
       Extended_queue takeoff;
       int queue_limit;//队列的最大长度
       int num_land_requests; //要求降落的飞机数目
       int num_takeoff_requests;//要求起飞的飞机数目
       int num_landing;//已降落的飞机数目
       int num_takeoffs;//已起飞的飞机数目
       int num_land_accepted;//在降落队列里的飞机数目
       int num_takeoff_accepted;//在起飞队列里的飞机数目
       int num_land_refused;//被拒绝的要降落飞机数目
       int num_takeoff_refused;//被拒绝的要起飞飞机数目
       int land_wait; //飞机等待降落的总时间
       int takeoff_wait;//飞机等待起飞的总时间
       int idle_time;//机场处于空闲状态的总时间
 };

 void Runway::shut_down(int time) const
//跑道数据在这里总结计算并打印出来
      {
              cout<< "Simulation has concluded after"<<time<<"time units"<<endl

                     <<" Total number of planes processed"
                     <<(num_land_requests+num_takeoff_requests)<<endl

                     <<"Total number of planes asking to land"
                     << num_land_requests<<endl

                     <<"Total number of planes asking to taking off"
                     << num_takeoff_requests<<endl

                     <<"Total number of planes accepted for landing"
                     << num_land_accepted<<endl

                     <<"Total number of planes accepted for takeoff"
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes refused for landing"
                     << num_takeoff_accepted<<endl

                    <<"Total number of planes refused for takeoff"
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes that landed"
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes that took off"
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes left landing queue"
                     << landing.size<<endl

                     <<"Total number of planes left in takeoff queue"
                     << takeoff.size<<endl;

            cout << "Percentage of time runway idle "<< 100.0 * ((float) idle_time)/((float) time) << "%" << endl;//跑道闲置时间的百分比

            cout << "Average wait in landing queue "<< ((float) land_wait)/((float) num_landing) << " time units";

            cout << endl << "Average wait in takeoff queue "<< ((float) takeoff_wait)/((float) num_takeoffs)<< " time units" << endl;

            cout << "Average observed rate of planes wanting to land "<< ((float) num_land_requests)/((float) time)<< " per time unit" << endl;

            cout << "Average observed rate of planes wanting to take off "<< ((float) num_takeoff_requests)/((float) time)<< " per time unit" << endl;
      }

void initialize(int &end_time, int &queue_limit, double &arrival_rate, double&departure_rate)
//用户在此声明仿真所需的time units（时间单位）的数量，队列的最大长度和机场的平均到达率和离开率。
{
    cout << "This program simulates an airport with only one runway." << endl
    << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
    << "or take off at any time? " << flush;
    cin >> queue_limit;
    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;
    bool acceptable;
    do {
    cout << "Expected number of arrivals per unit time?" << flush;
    cin >> arrival_rate;
    cout << "Expected number of departures per unit time?" << flush;
    cin >> departure_rate;
    if (arrival_rate < 0.0 || departure_rate < 0.0)
    cerr << "These rates must be nonnegative." << endl;
    else
    acceptable = true;
    if (acceptable && arrival_rate + departure_rate > 1.0)
    cerr << "Safety Warning: This airport will become saturated. " << endl;
    } while (!acceptable);

}


void main()
{
   int end_time;//运行总时间单位
   int queue_limit;//队列的最大长度（起飞、降落）
   int flight_number = 0;
   double arrival_rate, departure_rate;
   initialize(end_time,queue_limit,arrival_rate,departure_rate);
   Random variable;
   Runway small_airport(queue_limit);
   for (int current_time = 0; current_time<end_time;current_time++)
    {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++)
            {
                Plane current_plane(flight_number++, current_time, arriving);
                if (small_airport.can_land(current_plane) != success)
                    current_plane.refuse();
            }
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j<number_departures; j++)
            {
                Plane current_plane(flight_number++, current_time, departing);
                if (small_airport.can_depart(current_plane) != success)
                    current_plane.refuse();
            }
        Plane moving_plane;
        switch (small_airport.activity(current_time,moving_plane))
        {
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case  idle;
                run_idle(current_time);
        }
    }
    small_airport.shut_down(end_time);
 }


