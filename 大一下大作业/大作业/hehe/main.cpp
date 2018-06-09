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

static double queue_limit;//���е���󳤶ȣ���ɡ����䣩

enum Runway_activity {Idle, Land, Takeoff};
enum Plane_status{null, arriving, departing};
enum Error_code{success,underflow,overflow};

//���ɷֲ������
std::default_random_engine generator;
int poisson(double x)
{
  std::poisson_distribution<int> distribution(x);
  int number = distribution(generator);
  return number;
}

//��������Ƿ���ȷ
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
   template <typename T> friend class Extended_queue;//����������Ԫ�� ���ǿ��Ե��ñ���ĳ�Ա

private:
   int flt_num;//�����
   int clock_start;//��ʱ�� ��ע�ɻ����������ʱ��
   Plane_status state;//�ɻ�״̬
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
  friend class Runway;

 private:
  int size;//������󳤶�
  int front;//��ͷλ��
  int rear;//��βλ��
  T entry[15];//������󳤶�Ϊ15
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
       int queue_limit;//���е���󳤶�
       int num_land_requests=0; //Ҫ����ķɻ���Ŀ
       int num_takeoff_requests=0;//Ҫ����ɵķɻ���Ŀ
       int num_landing=0;//�ѽ���ķɻ���Ŀ
       int num_takeoffs=0;//����ɵķɻ���Ŀ
       int num_land_accepted=0;//�ڽ��������ķɻ���Ŀ
       int num_takeoff_accepted=0;//����ɶ�����ķɻ���Ŀ
       int num_land_refused=0;//���ܾ���Ҫ����ɻ���Ŀ
       int num_takeoff_refused=0;//���ܾ���Ҫ��ɷɻ���Ŀ
       int land_wait=0; //�ɻ��ȴ��������ʱ��
       int takeoff_wait=0;//�ɻ��ȴ���ɵ���ʱ��
       int idle_time=0;//�������ڿ���״̬����ʱ��
 };

 //���캯��
 Plane::Plane()
{
    flt_num = 0;
    clock_start = 0;
    state = null;
}

Plane::Plane(int flt, int time, Plane_status status):flt_num(flt),clock_start(time),state(status){}

//�ܾ�����
void Plane::refuseland(Runway &runway) const
{
    cout << "    Plane number " << setw(3) << left << flt_num << " told to try to land again later" << endl ;
    runway.num_land_refused++;
}

//�ܾ����
void Plane::refusetakeoff(Runway &runway) const
{
    cout << "    Plane number " << setw(3) << left << flt_num << " told to try to takeoff again later" << endl ;
    runway.num_takeoff_refused++;
}

//�ɻ�����
void Plane::land(int time) const
{
    cout << "Plane number " << setw(3) << left << flt_num << " landed after " << (time - clock_start) << " time units in the land queue" << endl;
}

//�ɻ����
void Plane::fly(int time) const
{
    cout << "Plane number " << setw(3) << left << flt_num << " took off after " << (time - clock_start) << " time units in the takeoff queue" << endl;
}

//��ʼ��
template <typename T>
Extended_queue <T>::Extended_queue()
{
    size = 0;
    front = 0 ;
    rear = 0;
}


//����Ƿ���
template <typename T>
bool Extended_queue<T>::full()const
{
    return (size == queue_limit) ? true : false;
}


//����Ƿ��
template <typename T>
bool Extended_queue <T> ::empty() const
{
    return (size == 0) ? true : false;
}

//����
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

//���
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

//ȡ��ͷԪ��
template <typename T>
Error_code Extended_queue <T> :: retrieve(T&item) const
{
    if (size == 0)
        return underflow;
    item = entry[front];
    return success;
}

 Runway::Runway(int limit) : queue_limit(limit){}

//�ж��Ƿ���Խ���
 Error_code Runway::can_land(const Plane& current)
 {
  cout << "    Plane number " << setw(3) << left << current.flt_num << " ready to land" <<  endl;
  num_land_requests++;
  if (landing.full())
    return overflow;
  else
    return success;
 }

//�ж��Ƿ�������
Error_code Runway::can_depart(const Plane& current)
{
  cout << "    Plane number " << setw(3) << left << current.flt_num << " ready to take off" << endl;
  num_takeoff_requests++;
if (takeoff.full())
    return overflow;
  else
    return success;
}

//���Խ��������
void Runway::accept_land (Plane &plane)
{
    landing.append(plane);
    num_land_accepted++;
}

//���Խ���ɶ���
void Runway::accept_takeoff (Plane &plane)
{
    takeoff.append(plane);
    num_takeoff_accepted++;
}

 //����������ķɻ� �����жϽ������
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

//�ܵ������������ܽ���㲢��ӡ����
 void Runway::shut_down(int time) const
      {

              cout<< "Simulation has concluded after  "<<time<<"  time units"<<endl


                     <<"Total number of planes processed                       " //����ķɻ�����

                     <<(num_land_requests+num_takeoff_requests)<<endl

                     <<"Total number of planes asking to land                  "//Ҫ����½�ķɻ�����
                     << num_land_requests<<endl

                     <<"Total number of planes asking to take off              "//Ҫ����ɵķɻ�����
                     << num_takeoff_requests<<endl

                     <<"Total number of planes accepted for landing            "//������½�ķɻ�����
                     << num_land_accepted<<endl

                     <<"Total number of planes accepted for takeoff            "//������ɵķɻ�����
                     << num_takeoff_accepted<<endl

                     <<"Total number of planes refused for landing             "//�ܾ���½�ķɻ�����
                     << num_land_refused<<endl

                     <<"Total number of planes refused for takeoff             "//�ܾ���ɵķɻ�����
                     << num_takeoff_refused<<endl

                     <<"Total number of planes that landed                     "//����ķɻ�����
                     << num_landing<<endl

                     <<"Total number of planes that took off                   "//��ɵķɻ�����
                     << num_takeoffs<<endl

                     <<"Total number of planes left in landing queue           "//��������ɶ�����ķɻ�����
                     << landing.size<<endl

                     <<"Total number of planes left in takeoff queue           "//�����ڽ��������ķɻ�����
                     << takeoff.size<<endl;

            cout     <<"Percentage of time runway idle                         "<< 100.0 * ((float) idle_time)/((float) time) << "%" << endl;//�ܵ�����ʱ��İٷֱ�

            cout     <<"Average wait in landing queue                          "<< ((float) land_wait)/((float) num_landing) << " time units" << endl;//ƽ���ڽ��������ȴ���ʱ��

            cout     <<"Average wait in takeoff queue                          "<< ((float) takeoff_wait)/((float) num_takeoffs)<< " time units" << endl;//ƽ������ɶ�����ȴ���ʱ��

            cout     <<"Average observed rate of planes wanting to land        "<< ((float) num_land_requests)/((float) time)<< " per time unit" << endl;//��Ҫ����ķɻ���ƽ���۲���

            cout     <<"Average observed rate of planes wanting to take off    "<< ((float) num_takeoff_requests)/((float) time)<< " per time unit" << endl;//ϣ����ɵķɻ���ƽ���۲���
      }

//�û��ڴ��������������time units��ʱ�䵥λ�������������е���󳤶Ⱥͻ�����ƽ�������ʺ��뿪�ʡ�
void initialize(double &end_time, double &queue_limit, double &arrival_rate, double&departure_rate)
{
    cout << "This program simulates an airport with only one runway." << endl
    << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
    << "or take off at any time? " << flush;
    EnterNum(queue_limit);
    cout << "How many units of time will the simulation run?" << flush;
    EnterNum(end_time);

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

//�ܵ�����
void run_idle(int &time)
{
  cout << "Runway is Idle. " << endl;
}

int main()
{
   double end_time;//������ʱ�䵥λ
   //int queue_limit;//���е���󳤶�
   double flight_number = 0;//��ʼ�����Ϊ0
   double arrival_rate, departure_rate;
   initialize(end_time,queue_limit,arrival_rate,departure_rate);
   Runway small_airport(queue_limit);
   for (int current_time = 0; current_time<end_time;current_time++)
    {
        int number_arrivals = poisson(arrival_rate);//������ɸ�ʱ�̽��ή��ķɻ���
        for (int i = 0; i < number_arrivals; i++)
            {
                Plane current_plane(flight_number++, current_time, arriving);
                if (small_airport.can_land(current_plane) == success)
                    small_airport.accept_land (current_plane);
                  else
                    current_plane.refuseland(small_airport);
            }
        int number_departures = poisson(departure_rate);//������ɸ�ʱ�̽�����ɵķɻ���
        for (int j = 0; j<number_departures; j++)
            {
                Plane current_plane(flight_number++, current_time, departing);
                if (small_airport.can_depart(current_plane) == success)
                    small_airport.accept_takeoff (current_plane);
                  else
                    current_plane.refusetakeoff(small_airport);
            }

        cout << setw(3) << left << current_time << ":" ;

        Plane moving_plane;//׼�������ķɻ�???
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
