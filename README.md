# Optimal-Collection-of-Pollution-Data

This project was based off of the Budget Maximum Coverage Problem by Samir Khuller, Anna Mossy, and Joseph Seffi Naor

Utilizing libraries such a cmath, queue, and vector, I was able to develop an algorithm similar to the pseudocode provided in the paper.

The main purpose of this project is to collect pollution data from data sensors from different areas in a city in a way that maximizes coverage, while remaining within budget. Each data sensor has a certain area that it covers, with any data sensors within that range contributing towards it's weight. 

These data sensors are spread out depending on two forms of distribution, normal and cluster. Each cluster in the cluster distribution is set at a certain point in the city. Income is based on the cluster location, and income then determines the asking price of user data.

For convenience purposes, the output displays the improvements my code has over a pure greedy algorithm and a random algorithm. 
I ran 100k different simulated cities, with each city having 4 clusters.
After multiple runs, my program has achieved a consistent 39% improvement over a random selection algorithm, and a 29% improvement over a pure greedy algorithm.
