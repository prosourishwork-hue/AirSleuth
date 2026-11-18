# AirSleuth – Delhi Pollution Source Detective

![C++](https://img.shields.io/badge/C++-17-blue) ![Type](https://img.shields.io/badge/Type-Console%20Application-lightgrey) ![SDG 11](https://img.shields.io/badge/SDG-11-orange) ![SDG 13](https://img.shields.io/badge/SDG-13-green)

AirSleuth is an object-oriented C++ console application that traces the most likely source of air pollution (industry, stubble burning, traffic, construction) at Delhi's monitoring stations, using wind direction, distance, and seasonal and time-of-day activity patterns.

It is a beginner-friendly OOPS lab mini-project mapped to **SDG 11: Sustainable Cities and Communities** and **SDG 13: Climate Action**.

## Table of Contents

- [Problem Statement](#problem-statement)
- [Objectives](#objectives)
- [SDG Mapping](#sdg-mapping)
- [Features](#features)
- [How It Works](#how-it-works)
- [OOP and C++ Concepts](#oop-and-c-concepts)
- [Project Structure](#project-structure)
- [How to Compile and Run](#how-to-compile-and-run)
- [Sample Output](#sample-output)
- [Limitations](#limitations)
- [Future Scope](#future-scope)
- [Note](#note)
- [Group Members](#group-members)

## Problem Statement

Delhi regularly records some of the worst air quality in the world, especially in the winter months. Monitoring stations report how polluted the air is, but they do not directly say **where the pollution is coming from**. Without knowing the likely source, it is hard to decide which control measures (traffic restrictions, construction bans, industrial checks, stubble-burning enforcement) will be most effective.

AirSleuth acts as a simple "detective": given a monitoring station, its pollutant readings, and the surrounding conditions, it estimates which source is the most probable contributor.

## Objectives

- Demonstrate core object-oriented programming concepts through a real-world environmental problem.
- Model pollution sources and monitoring stations as classes and objects.
- Combine wind direction, distance, season, and time of day to score each possible source.
- Present a ranked, easy-to-read result in a console interface.
- Allow results to be exported to a text file for record keeping.

## SDG Mapping

| Goal | How the project relates |
|------|-------------------------|
| **SDG 11: Sustainable Cities and Communities** | Supports better understanding of urban air quality and the sources that affect city residents. |
| **SDG 13: Climate Action** | Raises awareness of emission sources such as traffic, industry, and biomass burning that contribute to pollution and climate impact. |

## Features

- Register Delhi air-quality monitoring stations.
- Record pollutant readings (PM2.5, PM10) for each station.
- Model four pollution source types: industry, stubble burning, traffic, and construction.
- Score each source using wind direction, distance, season, and time of day.
- Rank all sources and display the most likely one for a selected station.
- Menu-driven console interface with input validation.
- Save a summary report to a text file.

## How It Works

1. **Input:** The user selects a monitoring station and provides conditions such as wind direction, season, and time of day.
2. **Scoring:** Each pollution source calculates its own likelihood score based on:
   - **Wind direction:** a source scores higher if the wind blows from its direction towards the station.
   - **Distance:** nearer sources score higher than distant ones.
   - **Season:** for example, stubble burning is most active in the post-harvest season (October to November).
   - **Time of day:** for example, traffic peaks during rush hours and construction during daytime.
3. **Ranking:** The scores are sorted from highest to lowest.
4. **Output:** The top-ranked source is reported as the most likely cause, along with the full ranking.

In simplified form:

```text
Final Score = Wind Factor × Distance Factor × Season Factor × Time-of-Day Factor
```

## OOP and C++ Concepts

| Concept | Where it is used |
|---------|------------------|
| **Classes and objects** | Stations, readings, and pollution sources are represented as objects. |
| **Encapsulation** | Data members are kept `private` and accessed through member functions. |
| **Constructors** | Used to initialise stations and sources with their data. |
| **Inheritance** | Specific sources (industry, stubble burning, traffic, construction) derive from a common base class. |
| **Polymorphism and virtual functions** | Each source type overrides the scoring function in its own way. |
| **Vectors (STL)** | Store collections of stations and sources dynamically. |
| **Loops and conditions** | Drive the menu, validation, and ranking logic. |
| **File handling** | Export the summary report to a text file using `ofstream`. |

## Project Structure

```text
AirSleuth/
├── main.cpp          # Source code (classes, logic, and menu)
├── README.md         # Project documentation
└── airsleuth_summary.txt   # Generated report (created at runtime)
```

## How to Compile and Run

**Requirements:** a C++ compiler such as `g++` (C++11 or later).

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

## Sample Output

```text
===== AirSleuth: Delhi Pollution Source Detective =====
1. Add monitoring station
2. Record pollutant readings
3. Analyse most likely source
4. Display ranking
5. Save summary to file
6. Exit
Enter your choice: 3

Station: Anand Vihar
Wind direction: North-West | Season: Winter | Time: Evening

Rank  Source             Score
1     Stubble Burning    0.82
2     Traffic            0.64
3     Industry           0.41
4     Construction       0.27

Most likely source: Stubble Burning
```

> The values above are for illustration only. Actual output depends on the data you enter.

## Limitations

- Data is stored in memory only and is lost when the program closes.
- Readings are entered manually rather than fetched from live monitoring systems.
- The scoring factors are simplified assumptions, not measured values.
- Only four source categories are modelled.

## Future Scope

- Load real-time data from official air-quality monitoring APIs.
- Store stations and readings permanently in files or a database.
- Add more sources such as power plants, waste burning, and road dust.
- Add a graphical or web-based interface with maps and charts.
- Improve accuracy with statistical or machine-learning models.

## Note

This is an educational console-based prototype. The source-scoring model is a simplified demonstration and is not a scientifically validated source-apportionment method. It should not be used for official air-quality assessment or policy decisions. Data is held in memory while the program runs.

## Group Members

- **SOURISH KHANDUJA** – 00714803125
- **RUPIN MADAN** – 00314803125
