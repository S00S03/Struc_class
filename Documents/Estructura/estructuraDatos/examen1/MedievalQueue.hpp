#ifndef MEDIEVAL_QUEUE_HPP
#define MEDIEVAL_QUEUE_HPP

#include <string>
class MedievalQueue {
  public:
    // constructor
    MedievalQueue();
    // destructor
    ~MedievalQueue();
    // copy constructor
    MedievalQueue(const MedievalQueue &other);

    // Add a new person to the queue
    void enqueue(std::string person, bool isNoble);
    void dequeue();

    // Get first element
    std::string front() const;

    bool isEmpty() const;

    void print() const;

    int getNumNobles() const;
    int getNumPlebeyos() const;

    // void getPosition(int position) const;

  private:
    std::string *Elements;
    int numElements;

    int numPlebeyos;
    int numNobles;
};

#endif // !MEDIEVAL_QUEUE_HPP
