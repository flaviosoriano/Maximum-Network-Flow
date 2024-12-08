# Maximum-Network-Flow
A fictional project showcasing graph-based diagnostics for power grids. Analyzes maximum capacity, unmet demand, energy loss, and critical connections. Implemented in C/C++ with robust documentation and examples.
## Overview
This project implements a diagnostic tool for analyzing power distribution networks, based on a fictional scenario involving a company named Metalmax. The tool simulates a power grid using graph theory to analyze energy flow, identify inefficiencies, and propose optimizations. 

The project is entirely fictional and created as a practical challenge to demonstrate skills in computational problem-solving and algorithm development.

## Features
- **Graph-Based Modeling**: Represents the power grid as a graph for efficient computation.
- **Energy Diagnostics**:
  - Determines the maximum energy capacity of the network.
  - Identifies unmet consumer demands.
  - Calculates energy losses during transmission.
- **Critical Connection Analysis**: Detects points of failure where connections operate at maximum capacity.
- **Example Dataset**: Includes fictional input and output scenarios for testing.

## Implementation Details
- **Languages**: C and C++.
- **Standards**: ANSI C (C99/C11/C17) and ISO/IEC C++ (C++11/C++14/C++17/C++20).
- **Compilation Flags**: 
  - `-Wall`, `-Wextra`, `-Wpedantic`, `-Wformat-security`, `-Wconversion`, `-Werror`.
- **Input/Output**:
  - Input: Standard input describing the network (nodes, edges, capacities).
  - Output: Diagnostic results printed to standard output.

## Project Structure
- **Source Code**: Modular and organized for clarity.
- **Documentation**: Detailed PDF explaining problem modeling, algorithms, and complexity analysis.
- **Makefile**: Simplifies building the project executable (`tp2`).
