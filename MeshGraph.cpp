#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    int numVertices = vertexPositions.size();
    vertices.resize(numVertices);
    adjList.resize(numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        vertices[i].id = i;
        vertices[i].position3D = vertexPositions[i];
    }

    for (int i = 0; i < edges.size(); i++)
    {
        int vertexId0 = edges[i].vertexId0;
        int vertexId1 = edges[i].vertexId1;
        adjList[vertexId0].push_back(&vertices[vertexId1]);
        adjList[vertexId1].push_back(&vertices[vertexId0]);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    double totalDistance = 0.0;
    int edgeCount = 0;

    for (int i = 0; i < vertices.size(); i++)
    {
        const Vertex& vertex = vertices[i];
        const std::list<Vertex*>& vertexAdjList = adjList[i];
        for (std::list<Vertex*>::const_iterator it = vertexAdjList.begin(); it != vertexAdjList.end(); ++it)
        {
            Vertex* neighbor = *it;

            double dx = vertex.position3D.x - neighbor->position3D.x;
            double dy = vertex.position3D.y - neighbor->position3D.y;
            double dz = vertex.position3D.z - neighbor->position3D.z;
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz);

            totalDistance += distance;
            edgeCount++;
        }
    }

    return totalDistance/edgeCount;
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    int totalEdges = TotalEdgeCount();
    int vertexCount = TotalVertexCount();
    return (double )(totalEdges) / vertexCount;
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    int totalEdges = 0;

    for (int i = 0; i < adjList.size(); i++)
    {
        totalEdges += adjList[i].size();
    }

    return totalEdges/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    if (vertexId < 0 || vertexId >= vertices.size())
    {
        return -1;
    }

    return adjList[vertexId].size();
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
    outVertexIds.clear();

    if (vertexId < 0 || vertexId >= vertices.size())
    {
        return;
    }

    const std::list<Vertex*>& vertexAdjList = adjList[vertexId];
    for (std::list<Vertex*>::const_iterator it = vertexAdjList.begin(); it != vertexAdjList.end(); ++it)
    {
        Vertex* neighbor = *it;
        outVertexIds.push_back(neighbor->id);
    }
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}