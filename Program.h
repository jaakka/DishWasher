#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
    public:
      virtual void loop() = 0;
      virtual int getDurationMs() = 0;
};

#endif