// FE_enum.h: defines enumerations
//
//////////////////////////////////////////////////////////////////////

#ifndef _FE_ENUM_H_05132007_
#define _FE_ENUM_H_05132007_

//-----------------------------------------------------------------------------
// Element Class:
// Defines the general category of element.
enum FE_Element_Class {
	FE_ELEM_SOLID,
	FE_ELEM_SHELL,
	FE_ELEM_BEAM,
	FE_ELEM_SURFACE,
	FE_ELEM_TRUSS,
	FE_ELEM_DISCRETE,
    FE_ELEM_FERGUSON_SHELL
};

//-----------------------------------------------------------------------------
// Element shapes:
// This defines the general element shape classes. This classification differs from the
// element types below, in that the latter is defined by a shape and integration rule.
enum FE_Element_Shape {
	ET_HEX8,
	ET_HEX20,
	ET_HEX27,
	ET_PENTA6,
	ET_TET4,
	ET_TET10,
	ET_TET15,
	ET_QUAD4,
	ET_TRI3,
	ET_TRUSS2
};

//-----------------------------------------------------------------------------
// Element types:
//  Note that these numbers are actually indices into the m_Traits array
//  of the ElementLibrary class so make sure the numbers correspond
//  with the entries into this array
//

enum FE_Element_Type {
	// 3D solid elements
	FE_HEX8G8,	
	FE_HEX8RI,
	FE_HEX8G1,	
	FE_TET4G1,	
	FE_TET4G4,		
	FE_PENTA6G6,	
	FE_TET10G1,
	FE_TET10G4,
	FE_TET10G8,
	FE_TET10GL11,
	FE_TET10G4RI1,
	FE_TET10G8RI4,
	FE_TET15G4,
	FE_TET15G8,
	FE_TET15G11,
	FE_TET15G15,
	FE_TET15G15RI4,
	FE_HEX20G27,
	FE_HEX27G27,

	// 2.5D surface elements
	FE_QUAD4G4,
	FE_QUAD4NI,
	FE_TRI3G1,
	FE_TRI3G3,
	FE_TRI3NI,
	FE_TRI6G3,
	FE_TRI6G4,
	FE_TRI6G7,
	FE_TRI6MG7,
	FE_TRI6GL7,
	FE_TRI6NI,
	FE_TRI7G3,
	FE_TRI7G4,
	FE_TRI7G7,
	FE_TRI7GL7,
	FE_QUAD8G9,
	FE_QUAD9G9,

	// shell elements
	FE_SHELL_QUAD,
	FE_SHELL_TRI,
    FE_FERGUSON_SHELL_QUAD,

	// truss elements
	FE_TRUSS,

	// discrete elements
	FE_DISCRETE,
};

//-----------------------------------------------------------------------------
//! Helper class for creating domain classes.
struct FE_Element_Spec
{
	FE_Element_Shape	eshape;
	FE_Element_Type		etype;
	bool				m_bthree_field_hex;
	bool				m_bthree_field_tet;
	bool				m_but4;
};

//-----------------------------------------------------------------------------
//! This lists the super-class id's that can be used to register new classes
//! with the kernel. It effectively defines the base class that a class
//! is derived from.
typedef unsigned int SUPER_CLASS_ID;
#define FETASK_ID                   0x0001	// derived from FECoreTask
#define FESOLVER_ID                 0x0002	// derived from FESolver
#define FEMATERIAL_ID               0x0003	// derived from FEMaterial
#define FEBODYLOAD_ID               0x0004	// derived from FEBodyLoad
#define FESURFACELOAD_ID            0x0005	// derived from FESurfaceLoad
#define FENLCONSTRAINT_ID           0x0006	// derived from FENLConstraint
#define FECOORDSYSMAP_ID            0x0007	// derived from FECoordSysMap
#define FEPLOTDATA_ID               0x0008	// derived from FEPlotData
//#define FEANALYSIS_ID               0x0009	// derived from FEAnalysis (Obsolete from 2.5)
#define FESURFACEPAIRINTERACTION_ID 0x000A	// derived from FESurfacePairInteraction
#define FENODELOGDATA_ID            0x000B	// derived from FENodeLogData
#define FEELEMLOGDATA_ID            0x000C	// derived from FElemLogData
#define FEOBJLOGDATA_ID             0x000D	// derived from FELogObjectData
#define FEBC_ID						0x000E	// derived from FEBoundaryCondition (TODO: This does not work yet)
#define FEGLOBALDATA_ID				0x000F	// derived from FEGlobalData
#define FERIGIDOBJECT_ID			0x0010	// derived from FECoreBase (TODO: work in progress)
#define FENLCLOGDATA_ID             0x0011	// derived from FELogNLConstraintData
#define FECALLBACK_ID				0x0012	// derived from FECallBack
#define FEDOMAIN_ID					0x0013	// derived from FEDomain (TODO: work in progress)
#define FEIC_ID						0x0014	// derived from initial condition

/////////////////////////////////////////////////////////////////////////////
// ENUM: Linear solvers
//  Defines the supported linear solvers. Note that some of these solvers
//  are only available on certain platforms
//

enum FE_Linear_Solver_Type {
	SKYLINE_SOLVER,
	PSLDLT_SOLVER,		// use only where available
	SUPERLU_SOLVER,		// use only where available
	SUPERLU_MT_SOLVER,	// use only where available
	PARDISO_SOLVER, 	// use only where available
	LU_SOLVER,
	WSMP_SOLVER,		// use only where available
	CG_ITERATIVE_SOLVER,
	RCICG_SOLVER,			// use only where available
	FGMRES_SOLVER,			// use only where available
	FGMRES_ILUT_SOLVER,		// use only where available
	FGMRES_ILU0_SOLVER		// use only where available
};

///////////////////////////////////////////////////////////////////////////////
// ENUM: Analysis types
//  Types of analysis that can be performed
// TODO: Make this a FESolver attribute
enum FE_Analysis_Type {
	FE_STATIC		= 0,
	FE_DYNAMIC		= 1,
	FE_STEADY_STATE	= 2
};

///////////////////////////////////////////////////////////////////////////////
// ENUM: rigid surfaces

enum FE_Rigid_Surface_Type {
	FE_RIGID_PLANE,
	FE_RIGID_SPHERE
};

//-----------------------------------------------------------------------------
// Plot level sets the frequency of writes to the plot file.
enum FE_Plot_Level {
	FE_PLOT_NEVER,			// don't output anything
	FE_PLOT_MAJOR_ITRS,		// only output major iterations (i.e. converged time steps)
	FE_PLOT_MINOR_ITRS,		// output minor iterations (i.e. every Newton iteration)
	FE_PLOT_MUST_POINTS,	// output only on must-points
	FE_PLOT_FINAL,			// only output final converged state
	FE_PLOT_AUGMENTATIONS	// plot state before augmentations
};

//-----------------------------------------------------------------------------
// Print level sets the frequency of output to the screen and log file
enum FE_Print_Level {
	FE_PRINT_DEFAULT,
	FE_PRINT_NEVER,
	FE_PRINT_PROGRESS,
	FE_PRINT_MAJOR_ITRS,
	FE_PRINT_MINOR_ITRS,
	FE_PRINT_MINOR_ITRS_EXP,
};

//-----------------------------------------------------------------------------
// Output level sets the frequency of data output is written to the log or data files.
enum FE_Output_Level {
	FE_OUTPUT_NEVER,
	FE_OUTPUT_MAJOR_ITRS,
	FE_OUTPUT_MINOR_ITRS,
	FE_OUTPUT_MUST_POINTS,
	FE_OUTPUT_FINAL
};

//-----------------------------------------------------------------------------
// Dump level determines the times the restart file is written
enum FE_Dump_Level {
	FE_DUMP_NEVER,			// never write a dump file
	FE_DUMP_MAJOR_ITRS,		// create a dump file at the end of each converged time step
	FE_DUMP_STEP			// create a dump file at the end of an analysis step
};

//-----------------------------------------------------------------------------
//! Domain classes
//! The domain class defines the general catergory of element types
//! NOTE: beams are not supported yet.
#define	FE_DOMAIN_SOLID		1
#define	FE_DOMAIN_SHELL		2
#define	FE_DOMAIN_BEAM		3
#define	FE_DOMAIN_SURFACE	4
#define	FE_DOMAIN_TRUSS		5
#define	FE_DOMAIN_DISCRETE	6

#endif // _FE_ENUM_H_05132007_
