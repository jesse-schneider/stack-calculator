class stack {

    public:
        //6 essential methods
        //default ctor
        stack();
        stack(char dummy);
        //copy ctor
        stack(stack const & that);
        //cpy assignment
        stack(stack && that) noexcept;
        //move ctor
        stack & operator = (stack const & that);
        //move assignment
        stack & operator = (stack && that) noexcept;
        //dtor
        ~stack();

        int getStackSize();
        void setStackSize(int stackSize);
        int getNextInt(int deduct);
        void push(int number);
        int pop();
        void print();
        void printC();
        
    private:
        int stackSize;
        int *stackArr = new int[256];
};