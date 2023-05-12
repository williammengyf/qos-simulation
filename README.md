# qos-simulation

Developer: Yifan Meng

This project implements simulations of Strict Priority Queueing (SPQ) and Deficit Round Robin (DRR) with ns-3.


## Usage

Finish installing and configuring ns-3. 
Place this folder inside **..../ns-3.x/scratch**. 
Before the simulation, make sure to modify the information in **spq-config.xml** and **drr-config.xml**.

```
# go to root directory
cd ..../ns-3.x

# run ns-3 simulation for SPQ
./ns3 run "scratch/qos-simulation/simulation --config=scratch/qos-simulation/spq-config.xml --mode=spq"

# run ns-3 simulation for DRR
./ns3 run "scratch/qos-simulation/simulation --config=scratch/qos-simulation/drr-config.xml --mode=drr"
```