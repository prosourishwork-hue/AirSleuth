# AirSleuth – Delhi Pollution Source Detective

An object-oriented C++ console application that traces the most likely source of air pollution (industry, stubble burning, traffic, construction) at Delhi's monitoring stations, using wind direction, distance, and seasonal and time-of-day activity patterns. Mapped to **SDG 11: Sustainable Cities and Communities** and **SDG 13: Climate Action**.

## Features

- Register Delhi air-quality monitoring stations.
- Record pollutant readings (PM2.5, PM10) for each station.
- Model pollution sources: industry, stubble burning, traffic, construction.
- Score each source using wind direction, distance, season, and time of day.
- Rank and display the most likely source for a station.
- Save a summary report to a text file.

## OOP and C++ concepts

Classes, objects, inheritance, polymorphism, virtual functions, encapsulation, constructors, vectors, loops, conditions, and file handling.

## How to compile and run

Using g++:

```bash
g++ main.cpp -o airsleuth
./airsleuth
```

On Windows:

```bash
g++ main.cpp -o airsleuth.exe
airsleuth.exe
```

## Note

This is an educational console-based prototype. The source-scoring model is a simplified demonstration and is not a scientifically validated source-apportionment method. Data is held in memory while the program runs.

## Group Members

- **SOURISH KHANDUJA** – 00714803125
- **RUPIN MADAN** – 00314803125
