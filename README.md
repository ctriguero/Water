# Water:

# (1) Package content:
**(1.1)** The program **solid_coordinates_Water.cpp**. 
- This program generates the **initial configuration** file (data input file) for **LAMMPS** which consist of a:
- A **solid membrane** with a **hole/pore**. The atoms are placed in the minimum energy distance of the Lennard-Jones potential.
- A random distribution of **TIP4P/2005** water molecules. With all the bonds and angles defined for **LAMMPS**.

**(1.2)** The **input files** for **LAMMPS** to run: *pre-equilibration*, *equilibration*, and the files to run **PLUMED** experiments to detect the water molecules inside the membrane, and biased dynamics.

**(1.3)** **Analysis**:
- Program to extract data from log file: **extract_log.cpp**.
- Program to draw the configurations: **Draw_Frames.cpp**.
- Program to generate a rotating gif of a frame: **rot.ini** **rot.sh**.

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

- **Note 1**: **LAMMPS** minimization can not be used with the rigid bonds we want to use. If we relax the rigid bond condition then we can use **LAMMPS** relaxation previously to perform the dynamics.

- **Note 2**: Use the script **run.sh** to run the LAMMPS simulations it has the paths to **LAMMPS**. Be sure that it is pointing to the right input file.

**(3.1)** **Pre-equilibration**: Perform an NVT simulation with a **small integration step** to *pre-equilibrate* the system. You can use the following LAMMPS input files to achieve this. We use first a very small step and then a larger one:

- Input file: **in.solid**                    ----> NVT with small integration step (dt=**0.001** fs, **50000** steps)
- Input file: **in.solid_restart**            ----> NVT with increased integration step (dt=**0.1** fs, **50000** steps)

**(3.2)** **Equilibration**: Once the water is *pre-equilibrated* (not going to crash but not really equilibrated) we can use an anisotropic barostat to converge into the right water density and achieve a real equilibration of the system. The expected liquid water [density for TIP4P/2005](http://aip.scitation.org/doi/10.1063/1.2121687) water is: **0.9979** gr/cm^3, which approximately translates into the number density of: **0.033** water molecules/Angstrom^3. 

- Input file: **in.solid_restart_barostat**   ----> NPT to converge to the right density (dt=**0.1** fs, **1000000** steps)

# (4) Detect water molecules inside the pore with PLUMED.
**(4.1)** We first use the **PLUMED** utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html) to detect molecules inside the pore. This run is not going to constraint or bias the simulation by any mean. It will just monitor the number of water molecules inside the pore.

- **Bandwidth**: Determined by the diameter of the pore. We need to fill the pore space. The diameter of the pore is **20** Angstroms. The bandwith in the dimensions *x* and *y* must be at least **10** Angstroms (In **PLUMED** **1** nanometer). In the *z* dimension we just need to cover the interatomic distance between membrane atoms wichh is rm. The bandwith in the *z* dimension should be around rm/2. This is **1.77** Angstroms (In **PLUMED** **0.177** nanometers).

**(4.2)** One can accomplish this using the following provided **PLUMED** and **LAMMPS** input files:

- Input file: **in.solid_restart_plumed**   ----> NPT (dt=**2.0** fs we can use this larger step now provided the simulation is in equilibrium, **X** steps)

- This **LAMMPS** input file will make use of the *fix plumed* which is defined in the **plumed.dat** file where the instructions for detecting molecules inside the pore are specified.

# (5) Control the number of water molecules inside the pore: 

- **Note 1**: To fix the number of molecules inside the pore we use the **PLUMED** utility **MOVING_CONSTRAINT** which is a kind of umbrella sampling. We also use the **PLUMED** utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html). We start with the equilibrium occupation value of the pore wich is aroun **80** water molecules. Then we start adding a parabolic potential with zero curvature at the beginning increasing to positive values and centered in the target value. In this way we steer the dynamics towards our target occupation of the pore.

- **Note 2**: In order to steer the dynamics towards our occupation target, **PLUMED** will introduce forces in the system. All atoms will be affected. We do not want this forces to affect the solid membrane as it must preserve the shape. If the *fix plumed* command is introduced after the set velocities to zero and fix forces to zero for the solid, **PLUMED** will introduce additional forces applied to the solid that will break the solid. In this case: the *velocity set* and the *fix forces* applied to the solid **don't commute** with *fix plumed* i.e. the order will completely alter the result of the simulation.

**(5.1)** **Experiment 1**: Low density in the pore.

**(5.1)** **Experiment 2**: High density in the pore.

