# Water:

(1) This program generates the data input file for LAMMPS which consist in a: 
(1.1) A solid membrane with a hole. The atoms are placed in the minimum energy distance of the Lennard-Jones potential
(1.2) A random distribution of TIP4P/2005 water molecules

(2) Operate with the program:
(2.1) Adjust the parameters of the membrane and quantity of water molecules:
- Lx=18, Ly=18, Lz=14 are integers or scaled to the distance for the minimum energy in the Lennard-Jones potential. In our case this is: rm=3.54575.
- radius=10, again in rm units. This is the pore radius
- molecules=2000. This is the number of water molecules to insert. For liquid water we want high density (rho=1) but this introduces unstable configurations and the dynamics could explode. In general for this box 2000 molecules gives a good compromise between high density and stability. Once the simulation is equilibrated, we can perform an isobaric simulation in order to compress the water to the right density.

(2.2) The compilation should use the c++11 version:

g++ -std=c++11 solid_coordinates_Water.cpp

(3) Stabilize simulation with LAMMPS
(3.1) LAMMPS minimization can not be used with the rigid bonds we want to use otherwise use LAMMPS relaxation previously to perform the dynamics.
(3.2) First use a NVT simulation with a small integration step.
(3.3) Once the water is equilibrated we can use an anisotropic barostat to converge into the right water density.

(4) You can use concatenated the following input lammps files to achieve this:

in.solid                    ----> NVT with small integration step
in.solid_restart            ----> NVT with increased integration step
in.solid_restart_barostat   ----> NPT to converge to the right density

