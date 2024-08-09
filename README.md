```mermaid

flowchart TD//

    subgraph ADS
        G(fa:fa-eye sensing)
        A(fa:fa-car perception/object_recognition) 
        H(fa:fa-gear control)
        I(fa:fa-code-branch plaanning)
        G --> A --> I --> H
    end

    subgraph Unreal Engine
        B(fa:fa-database Cooperative Perception Module)
        D(fa:fa-vr-cardboard HMI)
        C(fa:fa-brain Coordination Module ~POMDP~)
    end

    E(fa:fa-unity Simulator)
    F(fa:fa-user Operator)

    A -->|object_recognition| B 
    B -->|object_recognition| A
    B -->|Observation| C
    C -->|Action| B
    A -->|object_recognition| D
    B -->|Intervention Request| D
    D -->|Intervention Result| B
    I -->|scenario_planning| D
    E -->|Data|G
    D -->|Request|F
    F -->|Intervention| D
    G -->|Sensor data| D
    H -->|control data| E
    D -->|motion data| B



```
![Screenshot from 2024-08-09 08-16-12](https://github.com/user-attachments/assets/35531a8c-c356-4ec7-8974-bf8f5bda7f90)
