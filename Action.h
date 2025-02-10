class Action {
    public:
      virtual void execute() = 0;
      virtual bool isReady() = 0;
};