#include <stdio.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <iomanip>
#include <string.h>
#include <iomanip>
using namespace std;

static double queue_limit;//队列的最大长度（起飞、降落）

enum Runway_activity {Idle, Land, Takeoff};
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

//检查输入是否正确
void EnterNum(double& i)
{
    label:
    while(!(cin >> i))
    {
      cin.clear();
      cin.sync();

      cerr << "ERROR !!! Please enter an nonnegative integer number :";
    }
    int a = i;
    if (a != i || i <= 0 )
    {
      cerr << "ERROR !!! Please enter an nonnegative integer number :";
      goto label;
    }
}

template <typename T> class Extended_queue;
class Runway;

class Plane{
public:
    Plane();
   Plane(int flt, int time, Plane_status status);
   void refuseland(Runway &) const;
   void refusetakeoff(Runway &) const;
   void land(int time) const; 
   void fly(int time) const;

   friend class Runway;
   template <typename T> friend class Extended_queue;//声明两个友元类 它们可以调用本类的成员

private:
   int flt_num;//航班号
   int clock_start;//计时器 标注飞机到达机场的时刻
   Plane_status state;//飞机状态
};

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

 private:
  int size;//队列最大长度
  int front;//队头位置
  int rear;//队尾位置
  T entry[15];//数组最大长度为15
};

class Runway
{
    public:
       Runway(int limit);
       Error_code can_land(const Plane& current);
       Error_code can_depart(const Plane& current);
       Runway_activity activity(int time, Plane &moving);
       void shut_down(int time) const;
       void accept_land (Plane &plane);
       void accept_takeoff (Plane &plane);
       friend class Plane;

    private:
       Extended_queue <Plane> landing;
       Extended_queue <Plane> takeoff;
       int queue_limit;//队列的最大长度
       int num_land_requests=0; //要求降落的飞机数目
       int num_takeoff_requests=0;//要求起飞的飞机数目
       int num_landing=0;//已降落的飞机数目
       int num_takeoffs=0;//已起飞的飞机数目
       int num_land_accepted=0;//在降落队列里的飞机数目
       int num_takeoff_accepted=0;//在起飞队列里的飞机数目
       int num_land_refused=0;//被拒绝的要降落飞机数目
       int num_takeoff_refused=0;//被拒绝的要起飞飞机数目
       int land_wait=0; //飞机等待降落的总时间
       int takeoff_wait=0;//飞机等待起飞的总时间
       int idle_time=0;//机场处于空闲状态的总时间
 };

 //构造函数
 Plane::Plane()
{
    flt_num = 0;
    clock_start = 0;
    state = null;
}

Plane::Plane(int flt, int time, Plane_status status):flt_num(flt),clock_start(time),state(status){}

//拒绝降落
void Plane::refuseland(Runway &runway) const
{
    cout << "    Plane number " << setw(3) << left << flt_num << " told to try to land again later" << endl ;
    runway.num_land_refused++;
}

//拒绝起飞
void Plane::refusetakeoff(Runway &runway) const
{
    cout << "    Plane number " << setw(3) << left << flt_num << " told to try to takeoff again later" << endl ;
    runway.num_takeoff_refused++;
}

//飞机降落
void Plane::land(int time) const 
{
    cout << "Plane number " << setw(3) << left << flt_num << " landed after " << (time - clock_start) << " time units in the land queue" << endl;
}

//飞机起飞
void Plane::fly(int time) const
{
    cout << "Plane number " << setw(3) << left << flt_num << " took off after " << (time - clock_start) << " time units in the takeoff queue" << endl;
}

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


//检查是否空
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
        size--;
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

 Runway::Runway(int limit) : queue_limit(limit){}

//判断是否可以降落
 Error_code Runway::can_land(const Plane& current)
 {
  cout << "    Plane number " << setw(3) << left << current.flt_num << " ready to land" <<  endl;
  num_land_requests++;
  if (landing.full())
    return overflow;
  else
    return success;
 }

//判断是否可以起飞
Error_code Runway::can_depart(const Plane& current)
{
  cout << "    Plane number " << setw(3) << left << current.flt_num << " ready to take off" << endl;
  num_takeoff_requests++;
if (takeoff.full())
    return overflow;
  else
    return success;
}

//可以进降落队列
void Runway::accept_land (Plane &plane)
{
    landing.append(plane);
    num_land_accepted++;
}

//可以进起飞队列
void Runway::accept_takeoff (Plane &plane)
{
    takeoff.append(plane);
    num_takeoff_accepted++;
}

 //操作队列里的飞机 优先判断降落队列
Runway_activity Runway::activity(int time, Plane &moving)
{
    if(!landing.empty())
      {
        landing.retrieve(moving);
        landing.serve();
        num_landing++;
        land_wait+=time-moving.clock_start;
        return Land;
      }
    else if(!takeoff.empty())
      {
        takeoff.retrieve(moving);
        takeoff.serve();
        num_takeoffs++;
        takeoff_wait+=time-moving.clock_start;
        return Takeoff;
      }
    else
    {
      idle_time++;
      return Idle;
    }

}

//跑道数据在这里总结计算并打印出来
 void Runway::shut_down(int time) const
      {

              cout<< "Simulation has concluded after  "<<time<<"  time units"<<endl


                     <<"Total number of planes processed                       " //处理的飞机总数

                     <<(num_land_requests+num_takeoff_requests)<<endl

                     <<"Total number of planes asking to land                  "//要求着陆的飞机总数
                     << num_land_requests<<endl

                     <<"Total number of planes asking to take off              "//要求起飞的飞机总数
                     << num_takeoff_requests<<endl

                     <<"Total number of planes accepted for landing            "//接受着陆的飞机总数
                     << num_land_accepted<<endl

                     <<"Total number of planes accepted for takeoff            "//接受起飞的飞机总数
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes refused for landing             "//拒绝着陆的飞机总数
                     << num_land_refused<<endl

                     <<"Total number of planes refused for takeoff             "//拒绝起飞的飞机总数
                     << num_takeoff_refused<<endl

                     <<"Total number of planes that landed                     "//降落的飞机总数
                     << num_landing<<endl

                     <<"Total number of planes that took off                   "//起飞的飞机总数
                     << num_takeoffs<<endl

                     <<"Total number of planes left in landing queue           "//还留在起飞队列里的飞机总数
                     << landing.size<<endl

                     <<"Total number of planes left in takeoff queue           "//还留在降落队列里的飞机总数
                     << takeoff.size<<endl;

            cout     <<"Percentage of time runway idle                         "<< 100.0 * ((float) idle_time)/((float) time) << "%" << endl;//跑道闲置时间的百分比

            cout     <<"Average wait in landing queue                          "<< ((float) land_wait)/((float) num_landing) << " time units" << endl;//平均在降落队列里等待的时间

            cout     <<"Average wait in takeoff queue                          "<< ((float) takeoff_wait)/((float) num_takeoffs)<< " time units" << endl;//平均在起飞队列里等待的时间

            cout     <<"Average observed rate of planes wanting to land        "<< ((float) num_land_requests)/((float) time)<< " per time unit" << endl;//想要降落的飞机的平均观察率

            cout     <<"Average observed rate of planes wanting to take off    "<< ((float) num_takeoff_requests)/((float) time)<< " per time unit" << endl;//希望起飞的飞机的平均观察率
      }

//用户在此声明仿真所需的time units（时间单位）的数量，队列的最大长度和机场的平均到达率和离开率。
void initialize(double &end_time, double &queue_limit, double &arrival_rate, double&departure_rate)
{
    cout << "This program simulates an airport with only one runway." << endl
    << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
    << "or take off at any time? " << flush;
    EnterNum(queue_limit);    
    cout << "How many units of time will the simulation run?" << flush;
    EnterNum(end_time);  
    cout << "Expected number of arrivals per unit time?" << flush;
    EnterNum(arrival_rate); 
    cout << "Expected number of departures per unit time?" << flush;
    EnterNum(departure_rate); 
    if (arrival_rate + departure_rate > 1.0)
    cerr << "Safety Warning: This airport will become saturated. " << endl;

}

//跑道闲置
void run_idle(int &time)
{
  cout << "Runway is Idle. " << endl;
}

int main()
{
   double end_time;//运行总时间单位
   //int queue_limit;//队列的最大长度
   double flight_number = 0;//初始航班号为0
   double arrival_rate, departure_rate;
   initialize(end_time,queue_limit,arrival_rate,departure_rate);
   Runway small_airport(queue_limit);
   for (int current_time = 0; current_time<end_time;current_time++)
    {
        int number_arrivals = poisson(arrival_rate);//随机生成该时刻将会降落的飞机数
        for (int i = 0; i < number_arrivals; i++)
            {
                Plane current_plane(flight_number++, current_time, arriving);
                if (small_airport.can_land(current_plane) == success)
                    small_airport.accept_land (current_plane);
                  else
                    current_plane.refuseland(small_airport);
            }
        int number_departures = poisson(departure_rate);//随机生成该时刻将会起飞的飞机数
        for (int j = 0; j<number_departures; j++)
            {
                Plane current_plane(flight_number++, current_time, departing);
                if (small_airport.can_depart(current_plane) == success) 
                    small_airport.accept_takeoff (current_plane);
                  else
                    current_plane.refusetakeoff(small_airport);
            }

        cout << setw(3) << left << current_time << ":" ;

        Plane moving_plane;//准备操作的飞机???
        switch (small_airport.activity(current_time,moving_plane)) 
        {
            case Land:
                moving_plane.land(current_time);
                break;
            case Takeoff:
                moving_plane.fly(current_time);
                break;
            case  Idle:
                run_idle(current_time);
                break;
        }

    }
    small_airport.shut_down(end_time);

    return 0;
 }
