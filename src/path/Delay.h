

class Delay {
private:
    unsigned int length;
public:
    Delay(unsigned int ms) { length = ms; }
    unsigned int get_delay() { return length; } 
};