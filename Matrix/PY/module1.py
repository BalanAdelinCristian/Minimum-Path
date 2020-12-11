from collections import defaultdict 

#Class to represent a graph 
class Graph: 

	def minDistance(self,dist,queue): 
		# Initialize min value and min_index as -1 
		minimum = float("Inf"); 
		min_index = -1;
		
		# from the dist array,pick one which 
		# has min value and is in queue 
		for i in range(len(dist)): 
			if(dist[i] < minimum and i in queue): 
				minimum = dist[i]; 
				min_index = i; 
		return min_index; 


	# Function to print shortest path 
	def printPath(self, parent, j): 
		
		if parent[j] == -1 : 
			print (j, end = ' '); 
			return;
		self.printPath(parent , parent[j]); 
		print (j, end = ' ');
	


	def dijkstra(self, graph, src, dest): 
		row = len(graph); 
		col = len(graph[0]); 

		# The output array. dist[i] will hold 
		# the shortest distance from src to i 
		# Initialize all distances as INFINITE 
		dist = [float("Inf")] * row; 

		#Parent array to store 
		# shortest path tree 
		parent = [-1] * row; 

		# Distance of source vertex 
		# from itself is always 0 
		dist[src] = 0;
	
		# Add all vertices in queue 
		queue = []; 
		for i in range(row): 
			queue.append(i); 
			
		while queue: 

			# Pick the minimum dist vertex 
			# from the set of vertices 
			# from queue 
			u = self.minDistance(dist,queue); 

			# remove min element	 
			queue.remove(u);

			# Update dist value and parent 
			# index of the adjacent vertices of 
			# the picked vertex.
			for i in range(col): 
				if graph[u][i] and i in queue: 
					if(dist[u] + graph[u][i] < dist[i]): 
						dist[i] = dist[u] + graph[u][i];
						parent[i] = u; 

		# print the constructed distance array
		print(src, "-->", dest, "\t",dist[dest], "\t" , end = ' ');
		self.printPath(parent, dest);