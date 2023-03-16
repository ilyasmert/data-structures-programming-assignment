#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    elements = std::vector<HeapElement>();
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    
    for (int i = 0; i < elements.size(); i++)
    {
        if (elements[i].uniqueId == uniqueId)
        {
            return false;
        }
    }

    
    HeapElement newElement;
    newElement.uniqueId = uniqueId;
    newElement.weight = weight;
    elements.push_back(newElement);

    
    int i = elements.size() - 1;
    while (i > 0 && elements[(i - 1) / 2].weight > elements[i].weight)
    {
        std::swap(elements[(i - 1) / 2], elements[i]);
        i = (i - 1) / 2;
    }

    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if (elements.empty())
    {
        return false;
    }

    outUniqueId = elements[0].uniqueId;
    outWeight = elements[0].weight;

    elements[0] = elements.back();
    elements.pop_back();

    int currentIndex = 0;
    while (true)
    {
        int leftChildIndex = 2 * currentIndex + 1;
        int rightChildIndex = 2 * currentIndex + 2;

        if (leftChildIndex >= elements.size())
        {
            break;
        }

        int minIndex = currentIndex;
        if (elements[leftChildIndex].weight < elements[minIndex].weight)
        {
            minIndex = leftChildIndex;
        }

        if (rightChildIndex < elements.size() && elements[rightChildIndex].weight < elements[minIndex].weight)
        {
            minIndex = rightChildIndex;
        }

        if (minIndex == currentIndex)
        {
            break;
        }

        std::swap(elements[currentIndex], elements[minIndex]);
        currentIndex = minIndex;
    }

    return true;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    for (int i = 0; i < elements.size(); i++){
        if (elements[i].uniqueId == uniqueId){
            elements[i].weight = newWeight;

            
            int currentIndex = i;
            while (currentIndex > 0 && elements[currentIndex].weight < elements[(currentIndex - 1) / 2].weight){
                std::swap(elements[currentIndex], elements[(currentIndex - 1) / 2]);
                currentIndex = (currentIndex - 1) / 2;
            }

            while (true){
                int leftChildIndex = 2 * currentIndex + 1;
                int rightChildIndex = 2 * currentIndex + 2;

                if (leftChildIndex >= elements.size()){
                    break;
                }

                int minIndex = currentIndex;
                if (elements[leftChildIndex].weight < elements[minIndex].weight){
                    minIndex = leftChildIndex;
                }

                if (rightChildIndex < elements.size() && elements[rightChildIndex].weight < elements[minIndex].weight){
                    minIndex = rightChildIndex;
                }

                if (minIndex == currentIndex){
                    break;
                }

                std::swap(elements[currentIndex], elements[minIndex]);
                currentIndex = minIndex;
            }

            return true;
        }
    }

    return false;
    
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return elements.size();
}