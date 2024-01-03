template <typename T>
class MySmartPointer
{
public:
    MySmartPointer(T* pointer)
    {
        pc_pointer = pointer;
        pc_counter = new RefCounter();
        pc_counter->add();
    }

    MySmartPointer(const MySmartPointer& other)
    {
        pc_pointer = other.pc_pointer;
        pc_counter = other.pc_counter;
        pc_counter->add();
    }

    ~MySmartPointer()
    {
        if (pc_counter->dec() == 0)
        {
            delete pc_pointer;
            delete pc_counter;
        }
    }

    T& operator*() { return (*pc_pointer); }
    T* operator->() { return (pc_pointer); }

    MySmartPointer& operator=(const MySmartPointer& other)
    {
        if (this != &other) // Check for self-assignment
        {
            // Decrement the current reference count
            if (pc_counter->dec() == 0)
            {
                delete pc_pointer;
                delete pc_counter;
            }

            // Copy the pointer and counter from the other object
            pc_pointer = other.pc_pointer;
            pc_counter = other.pc_counter;
            pc_counter->add();
        }
        return *this;
    }

private:
    RefCounter* pc_counter;
    T* pc_pointer;
};


class RefCounter
{
public:
    RefCounter() : count(0) {} // Initialize count to 0
    int add() { return (++count); }
    int dec() { return (--count); }
    int get() { return count; }

private:
    int count;
};