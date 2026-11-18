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
   - **Wind direction:** a source scores higher if the wind blows from its
