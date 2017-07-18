# Water:

# (1) Package content:
**(1.1)** The program **solid_coordinates_Water.cpp**. This program generates the initial configuration file (data input file) for **LAMMPS** which consist of a:

- A **solid membrane** with a **hole/pore**. The atoms are placed in the minimum energy distance of the Lennard-Jones potential.
- A random distribution of TIP4P/2005 water molecules. With all the bonds and angles defined for LAMMPS.

**(1.2)** The input files for LAMMPS to run pre-equilibration, equilibration and first PLUMED experiments to detect the water molecules inside the membrane.

# (2) How to generate initial configuration: solid_coordinates_Water.cpp
**(2.1)** Adjust the parameters of the membrane and quantity of water molecules:
- Lx=**18**, Ly=**18**, Lz=**14** are integers or scaled to the distance for the minimum energy in the Lennard-Jones potential. In our case this is: rm=3.54575 Angstroms. So the membrane real measure is **60X60X50** A^3.
- radius=**10** Angstroms (not in rm units). This is the pore radius
- molecules=**2000**. This is the number of water molecules to insert. For liquid water we want high density (rho=1) but this introduces unstable configurations and the dynamics could explode. In general for this box 2000 molecules gives a good compromise between high density and stability. Once the simulation is equilibrated, we can perform an isobaric simulation in order to compress the water to the right density.

**(2.2)** The compilation should use the c++ 11 standard:

- g++ -std=c++11 solid_coordinates_Water.cpp

# (3) Stabilize simulation with LAMMPS
**(3.1)** Use the script **run.sh** to run the LAMMPS simulations it has the paths to LAMMPS. Be sure that it is pointing to the right input file.

**(3.2)** LAMMPS minimization can not be used with the rigid bonds we want to use otherwise use LAMMPS relaxation previously to perform the dynamics.

**(3.3)** Perform an NVT simulation with a small integration step to pre-equilibrate the system. You can use the following LAMMPS input files to achieve this. We use first a very small step and then a larger one:

- in.solid                    ----> NVT with small integration step (dt=**0.001** fs, **50000** steps)
- in.solid_restart            ----> NVT with increased integration step (dt=**0.1** fs, **50000** steps)

**(3.4)** Once the water is *pre-equilibrated* (not going to crash but not really equilibrated) we can use an anisotropic barostat to converge into the right water density and achieve a real equilibration of the system.

- in.solid_restart_barostat   ----> NPT to converge to the right density (dt=**0.1** fs, **1000000** steps)

# (5) Detect water molecules inside the pore with PLUMED.
**(5.1)** We first use the utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html) to detect molecules inside the pore. This run is not going to constraint or bias the simulation by any mean. It will just monitor the number of water molecules inside the pore.

**(5.2)** One can accomplish this using the following provided **PLUMED** and **LAMMPS** input files:

- in.solid_restart_plumed   ----> NPT (dt=**2.0** fs we can use this larger step now provided the simulation is in equilibrium, **X** steps)

- This LAMMPS input file will make use of the **plumed.dat** file where the instructions for detecting molecules inside the pore are specified.

# (6) Control the number of water molecules inside the pore with PLUMED.

