#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <string.h>
using namespace std;

static int queue_limit;//队列的最大长度（起飞、降落）


enum Plane_status{null, arriving, departing};
enum Error_code{success,underflow,overflow};

//泊松分布随机数
std::default_random_engine generator;
int poisson(double x)
{
  std::poisson_distribution<int> distribution(x);
  int number = distribution(generator);
  return number;
}

class Runway;
template <typename T> class Extended_queue;

class Plane{
public:
    Plane();
   Plane(int flt, int time, Plane_status status);
   void refuse() const;
   void land(int time) const;
   void fly(int time) const;
   int started() const;

   friend class Runway;
   template <typename T> friend class Extended_queue;

private:
   int flt_num;
   int clock_start;
   Plane_status state;
};

Plane::Plane()
{
    flt_num = 0;
    clock_start = 0;
    state = null;
}

Plane::Plane(int flt, int time, Plane_status status):flt_num(flt),clock_start(time),state(status){}

void Plane::refuse() const
{
      cout <<  "number  "  << flt_num << "  等阵啦你  " << endl;
}

void Plane::land(int time) const
{
    cout << "Plane number " << flt_num << " landed after " << " time units in the takeoff queue" << endl;

}

void Plane::fly(int time) const
{
    cout << "Plane number " << flt_num << " took off after " << " time units in the land queue" << endl;

}

int Plane::started() const
{

}

template <typename T> class Extended_queue
{
 public:
   Extended_queue();
  bool full()const;
  bool empty() const;
  Error_code serve();
  Error_code append(const T &item);
  Error_code retrieve(T &item) const;
  void clear();
  Error_code serve_and_retrieve(T &item);

  friend class Runway;
  friend class Plane;

 private:
  int size;
  int front;
  int rear;
  T entry[10];
};

//初始化
template <typename T>
Extended_queue <T>::Extended_queue()
{
    size = 0;
    front = 0 ;
    rear = 0;

}

//检查是否满
template <typename T>
bool Extended_queue<T>::full()const
{
    return (size == queue_limit) ? true : false;
}


//检查队是否空
template <typename T>
bool Extended_queue <T> ::empty() const
{
    return (size == 0) ? true : false;
}

//出队
template <typename T> 
Error_code Extended_queue <T> :: serve ()
{
    if (size)
    {
        delete &entry[front] ;
        front = ((front == queue_limit-1) ? 0 : (front + 1));
        return success;
    }
    else
        return underflow;
}

//入队
template <typename T>
Error_code Extended_queue <T> :: append (const T&item)
{
    if(size >= queue_limit)
        return overflow;
    size++;
    entry [rear] = item;
    rear = ((rear+1) == queue_limit) ? 0 : (rear+1);
    return success;
}

//取队头元素
template <typename T>
Error_code Extended_queue <T> :: retrieve(T&item) const
{
    if (size == 0)
        return underflow;
    item = entry[front];
    return success;
}

enum Runway_activity {Idle, Land, Takeoff};


class Runway
{
    public:
       Runway(int limit);
       Error_code can_land(const Plane& current);
       Error_code can_depart(const Plane& current);
       Runway_activity activity(int time, Plane &moving);
       void shut_down(int time) const;

       friend class Plane;
    private:
       Extended_queue <Plane> landing;
       Extended_queue <Plane> takeoff;
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

 Runway::Runway(int limit) : queue_limit(limit){}

//判断是否可以降落
 Error_code Runway::can_land(const Plane& current)
 {
  cout << "Plane number  " << current.flt_num << "  ready to land" << current.state << endl;
  if (landing.full())
    return overflow;
  else
    return success;
 }

//判断是否可以起飞
Error_code Runway::can_depart(const Plane& current)
{
  cout << "Plane number  " << current.flt_num << "  ready to take off" << current.state << endl;
if (landing.full())
    return overflow;
  else
    return success;
}


Runway_activity Runway::activity(int time, Plane &moving)// 如果是被拒绝的飞机就不入队
{
    switch(moving.state)
    {
      case arriving:
      landing.append (current);
      break;
      case departing:
      takeoff.append(current);
      break;
      case null:
      cout << "啦啦啦啦来了来了来了来了略略" ；
    }

    if(!landing.empty())
      {
        landing.retrieve(moving);
        landing.serve();
        return Land;
      }
    else if(!takeoff.empty())
      {
        takeoff.retrieve(moving);
        takeoff.serve();
        return Takeoff;
      }
    else

      return Idle;
}

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
    cin >> queue_limit;//队伍的最大长度
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


int main()
{
   int end_time;//运行总时间单位
   //int queue_limit;//队列的最大长度
   int flight_number = 0;//初始航班号为0
   double arrival_rate, departure_rate;//每单位时间起飞、降落的概率
   initialize(end_time,queue_limit,arrival_rate,departure_rate);//初始化
   Runway small_airport(queue_limit);//初始化跑道
   for (int current_time = 0; current_time<end_time;current_time++)
    {

        //处理来的飞机
        int number_arrivals = poisson(arrival_rate);//随机生成该时刻将会降落的飞机数
        for (int i = 0; i < number_arrivals; i++)
            {
                Plane current_plane(flight_number++, current_time, arriving);//给当前时间的飞机赋予航班号 标上降落状态
                if (small_airport.can_land(current_plane) != success)
                    current_plane.refuse();
            }
        int number_departures = poisson(departure_rate);//随机生成该时刻将会起飞的飞机数
        for (int j = 0; j<number_departures; j++)
            {
                Plane current_plane(flight_number++, current_time, departing);//给当前时间的飞机赋予航班号 标上起飞状态  不应该入队  可能被拒绝
                if (small_airport.can_depart(current_plane) != success)
                    current_plane.refuse();
            }

        //处理在队列中的飞机
        Plane moving_plane;//准备操作的飞机???
        switch (small_airport.activity(current_time,moving_plane))//将飞机根据状态入相应的队  
        {
            case Land:
                moving_plane.land(current_time);//飞机降落  功能在Plane类
                break;
            case Takeoff:
                moving_plane.fly(current_time);//飞机起飞  功能在Plane类
                break;
            case  Idle:
                //run_idle(current_time);//跑道闲置
                break;
        }
        cout << current_time << ":" << endl;
    }
    small_airport.shut_down(end_time);

    return 0;
 }