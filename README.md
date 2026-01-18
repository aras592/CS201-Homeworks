Course Information

Course: CS201 - Introduction to Programming (Data Structures)
University: Bilkent University
Semester: Fall 2025

Assignments Overview

Homework 1: MagicCard Game System

Files: MagicCard.h, MagicCard.cpp
Topic: Dynamic Memory Management & Game Logic Implementation
Key Concepts:

- Implementation of a card game system with players and card piles
- Dynamically allocated arrays for storing players and piles as they grow
- Player management (add/remove/print with unique ID validation)
- Four card colors (Red, Yellow, Green, Blue) with numbers 1-10
- Draw pile and discard pile management with specific game rules
- Card operations: draw from deck, switch hands between players, play cards
- Game mechanics where cards must match color or number of top discard pile card
- Constraints: Must use dynamically allocated arrays only (no fixed arrays, vectors, linked lists, or STL containers)

Homework 2: Sheep Disease Search Algorithms

Files: SearchAlgorithms.cpp, report PDF
Topic: Search Algorithms & Performance Analysis
Key Concepts:

Problem: Finding K closest sheep IDs to an infected/dead sheep in sorted arrays
Implementation of three search algorithms:

- Linear Search (O(N))
- Binary Search (O(logN))
- Jump Search (O(N/m + m) with m = √N)
- Adaptation of algorithms to find K closest values when target doesn't exist
- Experimental analysis with arrays of sizes 2³ to 2¹⁵
- Performance testing with different K values: K = 1, N/8, N/4, N/2
- Time complexity comparison and plotting
- Deliverables: Algorithm implementations + Comprehensive PDF report with tables, plots, and theoretical analysis

Homework 3: BilkentTourism System

Files: BilkentTourism.h, BilkentTourism.cpp
Topic: Linked List Implementation for Transportation System
Key Concepts:

- Implementation of a bus line management system using sorted linked lists
- Three main entities: Bus Lines, Stops, and Buses (all with unique IDs)
- Sorted linked lists for maintaining bus lines in ascending order by ID
- Stop management with ability to add stops to multiple lines
- Bus assignment to lines with driver information
- Complex queries: print buses in line, print buses passing through stop
- Constraints: Must use sorted linked lists only (no arrays, vectors, or STL containers)

Homework 4: TimeTravelEngine System

Files: TimeTravelEngine.h, TimeTravelEngine.cpp
Topic: Stack Data Structures & Time Travel Simulation
Key Concepts:

- Custom stack implementation without using STL containers
- TimeBranch class representing parallel timelines with:

- Past stack (limited capacity)
- Current location
- Future stack (limited capacity)
- TimeStone stack (unlimited capacity)
- Time travel operations:

- fastForward: Move forward in time (pushing to Past stack)
- rewind: Move backward in time (pushing to Future stack)
- travelTo: Create new timeline from current point
- Time stone mechanics for temporal checkpoints
- Branch merging functionality (bonus feature)
- Constraints: No STL containers allowed; must implement all stacks manually; strict capacity management
