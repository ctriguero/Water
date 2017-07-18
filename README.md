# Water:

# (1) Package content:
**(1.1)** The program **solid_coordinates_Water.cpp**. 
- This program generates the **initial configuration** file (data input file) for **LAMMPS** which consist of a:
- A **solid membrane** with a **hole/pore**. The atoms are placed in the minimum energy distance of the Lennard-Jones potential.
- A random distribution of **TIP4P/2005** water molecules. With all the bonds and angles defined for **LAMMPS**.

**(1.2)** The **input files** for **LAMMPS** to run: *pre-equilibration*, *equilibration*, and the files to run **PLUMED** experiments to detect the water molecules inside the membrane, and biased dynamics.

# (2) Initial configuration: Solid_Coordinates_Water.cpp
**(2.1)** Adjust the size parameters of the membrane and quantity of water molecules in the program:
- **Membrane size**: Lx=**18**, Ly=**18**, Lz=**14** are integers or scaled to the distance for the minimum energy in the Lennard-Jones potential. In our case this is: rm=**3.54575** Angstroms. This are in fact the number of membrane atoms in each dimension. So the membrane real measure is **60X60X50** Angstroms^3.
- **Membrane pore**: radius=**10.0** Angstroms. This is the pore radius. It is chosen to have **20.0** Angstroms of diameter centered in a surface of **60X60** Angstroms^2.
- **Water molecules**: molecules=**2000**. This is the number of water molecules to insert. For liquid water we want high density (rho=**1.0**) but this introduces unstable configurations and the dynamics could explode. In general for this box **2000** molecules gives a good compromise between high density and stability for the initial steps of the dynamics. Once the simulation is equilibrated, we can perform an isobaric simulation in order to compress the water to the right density.

**(2.2)** **Compilation**: The compilation should use the c++ 11 standard:

- g++ -std=c++11 solid_coordinates_Water.cpp

**(2.3)** **Run**: The program should run in less than a minute. It will generate two outputs:

- **solid.data**: This is the initial configuration data file for **LAMMPS**.
- **config.xyz**: This is an xyz file to visualize the initial configuration, for example with [vmd](http://www.ks.uiuc.edu/Research/vmd/).

# (3) Stabilize/Equilibrate the configuration with LAMMPS

**Note 1**: **LAMMPS** minimization can not be used with the rigid bonds we want to use. If we relax the rigid bond condition then we can use **LAMMPS** relaxation previously to perform the dynamics.

**Note 2**: Use the script **run.sh** to run the LAMMPS simulations it has the paths to **LAMMPS**. Be sure that it is pointing to the right input file.

**(3.1)** **Pre-equilibration**: Perform an NVT simulation with a **small integration step** to *pre-equilibrate* the system. You can use the following LAMMPS input files to achieve this. We use first a very small step and then a larger one:

- Input file: **in.solid**                    ----> NVT with small integration step (dt=**0.001** fs, **50000** steps)
- Input file: **in.solid_restart**            ----> NVT with increased integration step (dt=**0.1** fs, **50000** steps)

**(3.2)** **Equilibration**: Once the water is *pre-equilibrated* (not going to crash but not really equilibrated) we can use an anisotropic barostat to converge into the right water density and achieve a real equilibration of the system.

- Input file: **in.solid_restart_barostat**   ----> NPT to converge to the right density (dt=**0.1** fs, **1000000** steps)

# (5) Detect water molecules inside the pore with PLUMED.
**(5.1)** We first use the **PLUMED** utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html) to detect molecules inside the pore. This run is not going to constraint or bias the simulation by any mean. It will just monitor the number of water molecules inside the pore.

**(5.2)** One can accomplish this using the following provided **PLUMED** and **LAMMPS** input files:

- Input file: **in.solid_restart_plumed**   ----> NPT (dt=**2.0** fs we can use this larger step now provided the simulation is in equilibrium, **X** steps)

- This **LAMMPS** input file will make use of the *fix plumed* which is defined in the **plumed.dat** file where the instructions for detecting molecules inside the pore are specified.

# (6) Control the number of water molecules inside the pore with PLUMED.

