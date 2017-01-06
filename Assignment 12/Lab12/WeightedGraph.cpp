//--------------------------------------------------------------------
//
//  Laboratory 12                                    WeightedGraph.cpp
//
//--------------------------------------------------------------------

#ifndef WEIGHTEDGRAPH_CPP
#define WEIGHTEDGRAPH_CPP

using namespace std;

#include "WeightedGraph.h"
#include "config.h"


//--------------------------------------------------------------------

WeightedGraph::WeightedGraph(int maxNumber)

// Creates an empty graph. Allocates enough memory for maxNumber
// vertices (defaults to defMaxGraphSize).
{ 
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxNumber];
	adjMatrix = new int[maxSize * maxSize];
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

WeightedGraph::WeightedGraph(const WeightedGraph& other)

// Creates an empty graph. Allocates enough memory for maxNumber
// vertices (defaults to defMaxGraphSize).
{
	this->maxSize = other.maxSize;
	this->size = other.size;

	for (int i = 0; i < size; i++)
	{
		vertexList[i] = other.vertexList[i];
	}

	for (int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			adjMatrix[maxSize *row + column] = other.adjMatrix[maxSize * row + column];
		}
	}


}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

WeightedGraph& WeightedGraph:: operator= ( const WeightedGraph& other )

// Copies from another WeightedGraph. 
{
	
	if (this == &other) {	// Self-assignment attempt!
		return *this;
	}

	// If arrays are not large enough, delete current and create new
	if (maxSize < other.maxSize) {
		delete[] vertexList;
		delete[] adjMatrix;

		vertexList = new Vertex[other.maxSize];
		adjMatrix = new int[other.maxSize*other.maxSize];
	}

	maxSize = other.maxSize;
	size = other.size;

	for (int i = 0; i<size; i++) 
	{
		vertexList[i] = other.vertexList[i];
	}

	for (int row = 0; row<size; row++)
	{
		for (int col = 0; col<size; col++) 
		{
			adjMatrix[maxSize*row + col] = other.adjMatrix[maxSize*row + col];
	}
	}
}

//--------------------------------------------------------------------

WeightedGraph:: ~WeightedGraph ()

// Frees the memory used by a graph.
{
	delete[] adjMatrix;
	delete[] vertexList;
}

//--------------------------------------------------------------------

void WeightedGraph:: insertVertex ( const Vertex& newVertex ) throw ( logic_error )

// Inserts newVertex into a graph. If a vertex with the same label
// as newVertex already exists in the graph, then updates that
// vertex's data with newVertex's data.
{
	if (isFull())
		throw logic_error("Graph is Full.");
	int pos;
	pos = getIndex(newVertex.getLabel());
	
	if (pos == size)
	{
		size++;
		for (int i = 0; i < size; i++)
		{
			setEdge(size - 1, i, INFINITE_EDGE_WT);
			setEdge(i, size - 1, INFINITE_EDGE_WT);
		}
	}

	vertexList[size - 1] = newVertex;
}

//--------------------------------------------------------------------

void WeightedGraph:: insertEdge ( const string& v1, const string& v2, int wt )
    throw ( logic_error )
// Insert an edge with the specified weight between vertices
// v1 and v2.
{
	int pos1 = getIndex(v1);
	int pos2 = getIndex(v2);

	if (pos1 >= size)
		throw logic_error("V1 is invalid.");
	if (pos2 >= size)
		throw logic_error("v2 is invalid.");

	setEdge(pos1, pos2, wt);
	setEdge(pos2, pos1, wt);
}

//--------------------------------------------------------------------

bool WeightedGraph:: retrieveVertex ( const string& v, Vertex &vData ) const

// Searches a graph for vertex v. If the vertex is found, then copies
// the vertex data to vData and returns 1. Otherwise, returns 0 with
// vData undefined.
{
	for (int i = 0; i < size; i++)
	{
		if (vertexList[i].getLabel() == v)
		{
			vData = vertexList[i];
			return true;
		}
	}

	return false;
}

//--------------------------------------------------------------------

bool WeightedGraph:: getEdgeWeight ( const string& v1, const string& v2, int &wt ) const
    throw ( logic_error )

// If there is an edge connecting vertices v1 and v2, then returns 1
// with wt returning the weight of the edge. Otherwise, returns 0
// with wt undefined.
{
	int vertex1 = getIndex(v1); 
	int vertex2 = getIndex(v2);   

	if (vertex1 >= size)
		throw logic_error("vert1 is invalid");

	if (vertex2 >= size)
		throw logic_error("vert2 is invalid");

	wt = getEdge(vertex1, vertex2);  

	if (wt != INFINITE_EDGE_WT)
		return 1;
	else
		return 0; 
}

//--------------------------------------------------------------------

void WeightedGraph:: removeVertex ( const string& v ) throw ( logic_error )

// Removes vertex v from a graph.
{

	int vert = getIndex(v);   
	int j, k;                  

	if (vert >= size)                    
		throw logic_error("vert is invalid.");

	for (j = vert; j < size - 1; j++)    
		vertexList[j] = vertexList[j + 1];

	for (j = vert; j < size - 1; j++)    
		for (k = 0; k < size; k++)
			setEdge(j, k, getEdge(j + 1, k));

	for (j = vert; j < size - 1; j++)     
		for (k = 0; k < size; k++)
			setEdge(k, j, getEdge(k, j + 1));

	size--;

}

//--------------------------------------------------------------------

void WeightedGraph:: removeEdge ( const string& v1, const string& v2 ) throw ( logic_error )

// Removes the edge between vertices v1 and v2 from a graph.

{
	int pos1 = getIndex(v1);
	int pos2 = getIndex(v2);

	setEdge(pos1, pos2, INFINITE_EDGE_WT);
	setEdge(pos2, pos1, INFINITE_EDGE_WT);


}

//--------------------------------------------------------------------

void WeightedGraph:: clear ()

// Removes all the vertices and edges from a graph.

{ 
	size = 0;
}

//--------------------------------------------------------------------

bool WeightedGraph:: isEmpty () const

// Returns 1 if a graph is empty. Otherwise, returns 0.

{
	return (size == 0);
}

//--------------------------------------------------------------------

bool WeightedGraph:: isFull () const

// Returns 1 if a graph is full. Otherwise, returns 0.

{
	return (size == maxSize);
}

//--------------------------------------------------------------------

void WeightedGraph:: showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ ) {
           cout << row << '\t' << vertexList[row].getLabel();
#if LAB12_TEST2
	   cout << '\t' << vertexList[row].getColor();
#endif
	   cout << endl;
       }

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}



//--------------------------------------------------------------------
//
//  Facilitator functions
//

int WeightedGraph:: getIndex ( const string& v ) const

// Returns the adjacency matrix index for vertex v. Returns size if
// the vertex does not exist.

{
	int i;
	for (i = 0; i < size; i++)
	{
		if (vertexList[i].getLabel() == v)
			return i;
	}
	return i;
}
       
//--------------------------------------------------------------------

int WeightedGraph:: getEdge ( int row, int col ) const

// Gets adjMatrix[row][col].

{
	int wt;
	wt = adjMatrix[maxSize*row + col];
	return wt;
}

void WeightedGraph:: setEdge ( int row, int col, int wt )

// sets adjMatrix[row][col].

{
	adjMatrix[maxSize*row + col] = wt;
}


#endif