class Sensor {
  public:
    virtual void loop() = 0;
};

class WaterLevelSensor : public Sensor {
  public:
    WaterLevelSensor() {

    }
    void loop() override {

    }
  private:
    bool maxLevel = false;
};

class TemperatureSensor : public Sensor {
  public:
    TemperatureSensor() {

    }
    void loop() override {

    }
};

class SensorHandler
{
  public:

    static const int TOTAL_SENSORS = 2; 
    Sensor* sensors[TOTAL_SENSORS];

    void Begin() {
        sensors[0] = new WaterLevelSensor();
        sensors[1] = new TemperatureSensor();
    }  
    
    void Loop() {
        for (int i = 0; i < TOTAL_SENSORS; i++) {
            sensors[i]->loop();
        }
    }
};


class Action {
  public:
    virtual void execute() = 0;
    virtual bool isReady() = 0;
};

class AddWater : public Action {
  public:
    void execute() override {
      
    }
    bool isReady() override {
      return true;
    }
};

class AddSoap : public Action {
  public:
    void execute() override {
      
    }
    bool isReady() override {
      return true;
    }
};

class HeatWater : public Action {
    public:
      void execute() override {
        
      }
      bool isReady() override {
        return true;
      }
  };

class Program {
  public:
    virtual void loop() = 0;
    virtual int getDurationMs() = 0;
};

class QuickWashProgram : public Program {
  public:

    static const int TOTAL_ACTIONS = 2; 
    int currentAction = 0;
    Action* actions[TOTAL_ACTIONS];

    QuickWashProgram() {
        actions[0] = new AddWater();
        actions[1] = new HeatWater();
        actions[2] = new AddSoap();
    }

    void loop() override {

    }
    
    int getDurationMs() override {
      return 0;
    }
};

class UserControl {
    public:

        void Begin() {

        }

        void Loop() {
            
        }

        bool userScrollRight() {
            return true;
        }

        bool userScrollLeft() {
            return true;
        }

        bool userPress() {
            return true;
        }
};

UserControl userControl;
SensorHandler sensorHandler;

void Setup() {
    userControl.Begin();
    sensorHandler.Begin();
}

void Loop() {
    sensorHandler.Loop();
}