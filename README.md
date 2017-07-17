# Water:

# (1) This program generates the data input file for LAMMPS which consist in a: 
(1.1) A solid membrane with a hole. The atoms are placed in the minimum energy distance of the Lennard-Jones potential
(1.2) A random distribution of TIP4P/2005 water molecules

# (2) Operate with the program: solid_coordinates_Water.cpp
(2.1) Adjust the parameters of the membrane and quantity of water molecules:
- Lx=18, Ly=18, Lz=14 are integers or scaled to the distance for the minimum energy in the Lennard-Jones potential. In our case this is: rm=3.54575.
- radius=10, again in rm units. This is the pore radius
- molecules=2000. This is the number of water molecules to insert. For liquid water we want high density (rho=1) but this introduces unstable configurations and the dynamics could explode. In general for this box 2000 molecules gives a good compromise between high density and stability. Once the simulation is equilibrated, we can perform an isobaric simulation in order to compress the water to the right density.

(2.2) The compilation should use the c++11 version:

- g++ -std=c++11 solid_coordinates_Water.cpp

# (3) Stabilize simulation with LAMMPS
(3.1) Use the script run.sh to run the LAMMPS simulations it has the paths to LAMMPS

(3.2) LAMMPS minimization can not be used with the rigid bonds we want to use otherwise use LAMMPS relaxation previously to perform the dynamics.

(3.3) First use a NVT simulation with a small integration step.

(3.4) Once the water is equilibrated we can use an anisotropic barostat to converge into the right water density.

# (4) You can use concatenated the following input lammps files to achieve this:
(4.1) in.solid                    ----> NVT with small integration step (dt=0.001 fs, 50000 steps)

(4.2) in.solid_restart            ----> NVT with increased integration step (dt=0.1 fs, 50000 steps)

(4.3) in.solid_restart_barostat   ----> NPT to converge to the right density (dt=0.1 fs, 1000000 steps)

# (5) We can now start to try with plumed inenvelope to detect molecules inside the pore

(5.1) in.solid_restart_plumed   ----> NPT to converge to the right density (dt=2.0 fs, X steps)

- This run will make use of the plumed.dat file where the instructions for detecting molecules inside the pore are specified.

