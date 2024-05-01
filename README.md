# Traffic Simulation: Processing Car Arrivals and Traffic Light Control

This program simulates a basic traffic management system, where cars arrive at specific times and directions, and a traffic light system switches between roads based on incoming traffic. This system is designed to avoid race conditions and synchronization issues by using mutexes and controlled threading.

## Table of Contents
- [Purpose](#purpose)
- [Overview](#overview)
- [File Structure](#file-structure)
- [How It Works](#how-it-works)
  - [Traffic Light Control](#traffic-light-control)
  - [Car Arrival Processing](#car-arrival-processing)

## Purpose
The purpose of this program is to demonstrate a simple traffic simulation where cars arrive at specified times from different directions, and a traffic light system manages the flow to avoid collisions or traffic jams.

## Overview
The code consists of three key components:
- **Traffic Light Control**: Determines when the traffic light should switch between two roads (A and B).
- **Car Arrival Processing**: Handles car arrivals at specific times and in specific directions.
- **Thread Synchronization**: Ensures thread safety when multiple threads are involved, using mutexes to avoid race conditions.

## File Structure
- **`main.cpp`**: Contains the main program logic, including the `processCars` function and thread handling.
- **`carArrived`**: A helper function to handle the event of a car arriving.
- **`turnGreen`**: A helper function to determine when to switch the traffic light.

## How It Works
### Traffic Light Control
The `turnGreen` function is responsible for deciding whether the traffic light should switch from one road to another. It uses a mutex to ensure that changing the traffic light is thread-safe. If a switch occurs, the function updates the previous direction.

### Car Arrival Processing
The `processCars` function processes a deque of cars with their arrival times and directions. It uses controlled threading to simulate car arrivals with timed delays. The function also checks if the traffic light should switch based on the car's direction and keeps a count of cars on each road.
