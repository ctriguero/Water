# Water:

# (1) Package content:
**(1.1)** The program **Water_data.cpp**.
- This program generates the **initial configuration** file (data input file) for **LAMMPS** which consist of a set of TIP4P/2005 water model in a box. The purpose of this program is just get some experience in water simulation that then we will use as enrironment for the membrane.

**(1.2)** The **input files** for **LAMMPS** to run: *pre-equilibration*, and the *equilibration* of liquid water.
- Input file: **in.water_NVT1_1**  
- Input file: **in.water_NPT1_2**
- Input file: **in.water_NVT2_3**
- Input file: **in.water_NPT2_4**
- Input file: **in.water_NVT3_5**
- Input file: **in.water_NPT3_6**

**(1.3)** The program **solid_coordinates_Water.cpp**. 
- This program generates the **initial configuration** file (data input file) for **LAMMPS** which consist of a:
- A **solid membrane** with a **hole/pore**. The atoms are placed in the minimum energy distance of the Lennard-Jones interaction potential for the *Oxygen-Oxygen interaction* given by the parameters of the **TIP4P/2005** water model.
- A random distribution of **TIP4P/2005** water molecules. With all the bonds and angles defined for **LAMMPS**.

**(1.4)** The **input files** for **LAMMPS** to run: *pre-equilibration*, *equilibration*, and the files to run **PLUMED** experiments to detect the water molecules inside the membrane, and biased dynamics.

**(1.5)** **Analysis**:
- Program to extract data from log file: **extract_log.cpp**.
- Program to draw the configurations: **Draw_Frames.cpp**.
- Program to generate a rotating gif of a frame: **rot.ini** **rot.sh**.

# (2) Initial configuration: solid_coordinates_Water_layer_170724.cpp
**(2.1)** Adjust the size parameters of the membrane and quantity of water molecules in the program:
- **Membrane size**: Lx=**18**, Ly=**18**, Lz=**14** are integers or scaled to the distance for the minimum energy in the Lennard-Jones potential. In our case this is: rm=**3.54575** Angstroms. This are in fact the number of membrane atoms in each dimension. So the membrane real measure is **60X60X50** Angstroms^3.
- **Membrane pore**: radius=**10.0** Angstroms. This is the pore radius. It is chosen to have **20.0** Angstroms of diameter centered in a surface of **60X60** Angstroms^2.
- **Water molecules**: molecules=**4500**. This is the number of water molecules to insert. For liquid water we want high density (rho=**1.0**) but this introduces unstable configurations and the dynamics could explode. In general for this box **4500** molecules gives a good compromise between high density and stability for the initial steps of the dynamics. Once the simulation is equilibrated, we can increase the time step.

**(2.2)** **Compilation**: The compilation should use the c++ 11 standard:

- g++ -std=c++11 solid_coordinates_Water.cpp

**(2.3)** **Run**: The program should run in less than a minute. It will generate two outputs:

- **solid.data**: This is the initial configuration data file for **LAMMPS**.
- **config.xyz**: This is an xyz file to visualize the initial configuration, for example with [vmd](http://www.ks.uiuc.edu/Research/vmd/).

# (3) Stabilize/Equilibrate the configuration with LAMMPS

- **Note 1**: **LAMMPS** minimization can not be used with the rigid bonds we want to use. If we relax the rigid bond condition then we can use **LAMMPS** relaxation previously to perform the dynamics.

- **Note 2**: Use the script **run.sh** to run the LAMMPS simulations it has the paths to **LAMMPS**. Be sure that it is pointing to the right input file.

**(3.1)** **Equilibration protocol**.
**(3.2)** **Pre-equilibration**: Perform an NVT simulation with a **small integration step** to *pre-equilibrate* the system. You can use the following LAMMPS input files to achieve this. We use first a very small step and then a larger one:

- Input file: **in.solid**                    ----> NVT with small integration step (dt=**0.001** fs, **50000** steps)
- Input file: **in.solid_restart**            ----> NVT with increased integration step (dt=**0.1** fs, **50000** steps)

**(3.3)** **Equilibration**: Once the water is *pre-equilibrated* (not going to crash but not really equilibrated) we can use an anisotropic barostat to converge into the right water density and achieve a real equilibration of the system. The expected liquid water [density for TIP4P/2005](http://aip.scitation.org/doi/10.1063/1.2121687) water is: **0.9979** gr/cm^3, which approximately translates into the number density of: **0.033** water molecules/Angstrom^3. Using the program  **extract_log.cpp** we can determine if the right number density has been reached: \rho=**2000** h2o molecules/(Lx A Ly A (Lz A-50 A)+\pi 10^2 A^2*50 A).

- Input file: **in.solid_restart_barostat**   ----> NPT to converge to the right density (dt=**0.1** fs, **1000000** steps)

# (4) Add more water to the initial configuration
**(4.1)** It is very likely that after the equilibration the water is condensed in to a much samaller region than the box. We might be interested in adding more water molecules to the configuration. In this case we should isolate the last frame from the equilibrations made in section **(3)**.
- For high densities the program could add some atom inside the membrane. As the pore is hydrophobic we can add a restriction in *z* to avoid add atoms inside the membrane and have a cleaner simulation.

**(4.2)** Once we have the last frame e.g. *lastframe.lammpstrj* we use the program **Add_more_water.cpp** to introduce more molecules. With this we create a new **LAMMPS** data file.
**(4.3)** **Compilation**: The compilation should use the c++ 11 standard:

- g++ -std=c++11 solid_coordinates_Water.cpp

**(4.4)** **Run**: The program should run in around one minute when **2500** water molecules are added to the pre-existing **4500**. It will generate two outputs:

- **solid_add.data**: This is the new initial configuration data file for **LAMMPS**.
- **config.xyz**: This is an xyz file to visualize the new initial configuration, for example with [vmd](http://www.ks.uiuc.edu/Research/vmd/).

**(4.5)** **Equilibration**: The new added water molecules are not in equilibrium. We need to equilibrate the system. We can use for that the same protocol used for the first data file in section **(3.1-2)**, with the new data file. In our specific example we added **2500** extra water molecules. Added to the **4500** that we already had makes **7000** water molecules. For the equilibration we use the following files:

- **solid_add.data**: This is the new initial configuration data file for **LAMMPS**.
- **in.membrane_NVT_hybrid_1**: This is the same **LAMMPS** input file used for the equilibration in section **(3.1-2)**.

# (5) Detect water molecules inside the pore with PLUMED.
**(5.1)** We first use the **PLUMED** utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html) to detect molecules inside the pore. This run is not going to constraint or bias the simulation by any mean. It will just monitor the number of water molecules inside the pore.

- **Bandwidth**: Determined by the diameter of the pore. We need to fill the pore space. The diameter of the pore is **20** Angstroms. The bandwith in the dimensions *x* and *y* must be at least **10** Angstroms (In **PLUMED** **1** nanometer). In the *z* dimension we just need to cover the interatomic distance between membrane atoms wichh is rm. The bandwith in the *z* dimension should be around rm/2. This is **1.77** Angstroms (In **PLUMED** **0.177** nanometers).

**(5.2)** One can accomplish this using the following provided **PLUMED** and **LAMMPS** input files:

- Input file: **in.solid_restart_plumed**   ----> NPT (dt=**2.0** fs we can use this larger step now provided the simulation is in equilibrium, **X** steps)

- This **LAMMPS** input file will make use of the *fix plumed* which is defined in the **plumed.dat** file where the instructions for detecting molecules inside the pore are specified.

# (6) Control the number of water molecules inside the pore: 

- **Note 1**: To fix the number of molecules inside the pore we use the **PLUMED** utility **MOVING_CONSTRAINT** which is a kind of umbrella sampling. We also use the **PLUMED** utility [INENVELOPE](http://plumed.github.io/doc-master/user-doc/html/_i_n_e_n_v_e_l_o_p_e.html). We start with the equilibrium occupation value of the pore wich is aroun **80** water molecules. Then we start adding a parabolic potential with zero curvature at the beginning increasing to positive values and centered in the target value. In this way we steer the dynamics towards our target occupation of the pore.

- **Note 2**: In order to steer the dynamics towards our occupation target, **PLUMED** will introduce forces in the system. All atoms will be affected. We do not want this forces to affect the solid membrane as it must preserve the shape. If the *fix plumed* command is introduced after the set velocities to zero and fix forces to zero for the solid, **PLUMED** will introduce additional forces applied to the solid that will break the solid. In this case: the *velocity set* and the *fix forces* applied to the solid **don't commute** with *fix plumed* i.e. the order will completely alter the result of the simulation.

- **Note 3**: The relaxed configuration does not contain any water molecule inside the pore. The pore is probably hydrophobic (we will check this later). The interactions among water decrease more the energy than the interactions between the water and membrane because there is not electrostatic interaction in this last one. For this reason the initial state is an empty pore.


**(6.1)** **Experiment 1**: Fill the pore with water molecules. We just need to steer the Oxygen atoms of the molecules as the hydrogens are bounded and will follow the oxygen. Different fillings have been tried.

**(6.1)** **Experiment 2**: Free evolution to se how it empties which shows the hydrophobicity of the pore (this is just an electrostatic effect. The walls of the pore do not interact electrostatically so water prefers stay with water in big bulks rather than in thin pores).

# (7) Clusters of water molecules inside the pore:

- **Note 1**: We will use two different clustering techniques. *Distance* and *Topological* clustering.
- **Note 2**: The parameters of the switching function to **insert the molecules** and to **pass the set of atoms** to the clustering algorithm need to be set differently. While to insert molecules we use the smoothness of the switching function to define the set of atoms we need something more radical that is usually controled with D_MAX. The problem is that as the switching function (sw) is defined as 1-sw the sense of D_MAX is lost. This is a problem that should be fix in **PLUMED**.

- To drive and insert molecules inside the pore:

d1: DENSITY SPECIES=4201-17700:3 LOWMEM
fi: INENVELOPE DATA=d1 ATOMS=1-3000 CONTOUR={RATIONAL D_0=0.1 R_0=0.5 D_MAX=10.0} BANDWIDTH=2.5,2.5,0.35 LOWMEM

- To define the set of atoms inside the pore:

d1: DENSITY SPECIES=4201-17700:3 LOWMEM
zi: INENVELOPE DATA=d1 ATOMS=1-3000 CONTOUR={RATIONAL D_0=0.5 R_0=0.2} BANDWIDTH=2.5,2.5,0.35 LOWMEM
matD: CONTACT_MATRIX ATOMS=zi SWITCH={RATIONAL D_0=0.5 R_0=0.1 D_MAX=0.7}  #{RATIONAL D_0=0.8 R_0=0.1 D_MAX=1.0}
DFSCLUSTERING MATRIX=matD LABEL=ssD

cvD: CLUSTER_PROPERTIES CLUSTERS=ssD CLUSTER=1 SUM
size1D: CLUSTER_NATOMS CLUSTERS=ssD CLUSTER=1
size2D: CLUSTER_NATOMS CLUSTERS=ssD CLUSTER=2
PRINT ARG=cvD.*  FILE=CvD.dat STRIDE=100
PRINT ARG=size1D FILE=SizeD1.dat STRIDE=100
PRINT ARG=size2D FILE=SizeD2.dat STRIDE=100
matA: TOPOLOGY_MATRIX NODES=zi ATOMS=4201-17700:3 BIN_SIZE=0.6 CYLINDER_SWITCH={RATIONAL  R_0=0.05 D_MAX=0.10} SWITCH={RATIONAL D_0=5.0 R_0=2.0 D_MAX=10.0} RADIUS={RATIONAL D_0=0.07 R_0=0.005 D_MAX=0.12} SIGMA=0.34 KERNEL=triangular DENSITY_THRESHOLD={RATIONAL D_0=0.0 R_0=0.001  D_MAX=0.01}
DFSCLUSTERING MATRIX=matA LABEL=ssA
cvA: CLUSTER_PROPERTIES CLUSTERS=ssA CLUSTER=1 SUM


