#include <iostream>
#include <mutex>
#include <deque>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

std::mutex m;

bool turnGreen(int direction, int& prevDirection)
{
    char roadName = (direction <= 2) ? 'A' : 'B';
    char prevRoadName = (prevDirection <= 2) ? 'A' : 'B';

    std::lock_guard<std::mutex> guard(m);

    if (roadName != prevRoadName)
    {
        std::cout << "Turn green for road " << roadName << std::endl;
        prevDirection = direction; 
        return true;
    }
    return false;
}

void carArrived(int carId, int direction)
{
    char roadName = (direction <= 2) ? 'A' : 'B';
    std::lock_guard<std::mutex> guard(m); 
    std::cout << "Car " << carId << " passed road " << roadName << " in direction " << direction << std::endl;
}

void processCars(const std::deque<int>& cars, const std::deque<int>& directions, const std::deque<int>& arrivalTime)
{
    int prevDirection = directions[0]; 

    std::vector<std::thread> threads;

    std::vector<int> onRoad{ 0, 0, 0, 0 };
    std::vector<int> limit{ 2, 2, 1, 1 };

    for (size_t i = 0; i < cars.size(); i++)
    {
        if (i > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds((arrivalTime[i] - arrivalTime[i - 1]) * 10));
        }

        if (turnGreen(directions[i], prevDirection))
        {
            std::fill(onRoad.begin(), onRoad.end(), 0);
        }

        onRoad[directions[i] - 1]++; 

       
        carArrived(cars[i], directions[i]);
    }

   
    for (auto& thread : threads)
    {
        thread.join();
    }
}

int main()
{
    std::deque<int> cars = { 1, 2, 3, 4, 5 };
    std::deque<int> directions = { 2, 3, 1, 3, 4};
    std::deque<int> arrivalTime = { 10, 20, 30, 40, 50 };

    processCars(cars, directions, arrivalTime);

    return 0;
}
