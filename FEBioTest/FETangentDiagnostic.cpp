// FETangentDiagnostic.cpp: implementation of the FETangentDiagnostic class.
//
//////////////////////////////////////////////////////////////////////

#include "FETangentDiagnostic.h"
#include "FEBioLib/FEBox.h"
#include "FEBioMech/FESolidSolver2.h"
#include "FEBioMech/FEElasticSolidDomain.h"
#include "FECore/log.h"

//-----------------------------------------------------------------------------
// Helper function to print a matrix
void print_matrix(matrix& m)
{
	int i, j;
	int N = m.rows();
	int M = m.columns();

	felog.printf("\n    ");
	for (i=0; i<N; ++i) felog.printf("%15d ", i);
	felog.printf("\n----");
	for (i=0; i<N; ++i) felog.printf("----------------", i);

	for (i=0; i<N; ++i)
	{
		felog.printf("\n%2d: ", i);
		for (j=0; j<M; ++j)
		{
			felog.printf("%15lg ", m[i][j]);
		}
	}
	felog.printf("\n");
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
BEGIN_PARAMETER_LIST(FETangentUniaxial, FEDiagnosticScenario)
	ADD_PARAMETER(m_strain, FE_PARAM_DOUBLE, "strain");
END_PARAMETER_LIST();

//-----------------------------------------------------------------------------
bool FETangentUniaxial::Init()
{
	FEModel& fem = GetDiagnostic()->GetFEModel();

	int i;
	vec3d r[8] = {
		vec3d(0,0,0), vec3d(1,0,0), vec3d(1,1,0), vec3d(0,1,0),
		vec3d(0,0,1), vec3d(1,0,1), vec3d(1,1,1), vec3d(0,1,1)
	};

	int BC[8][3] = {
		{-1,-1,-1},{ 0,-1,-1},{ 0, 0,-1}, {-1, 0,-1},
		{-1,-1, 0},{ 0,-1, 0},{ 0, 0, 0}, {-1, 0, 0}
	};

	// --- create the FE problem ---
	// create the mesh
	FEMesh& m = fem.GetMesh();
	m.CreateNodes(8);
	for (i=0; i<8; ++i)
	{
		FENode& n = m.Node(i);
		n.m_rt = n.m_r0 = r[i];
		n.m_rid = -1;

		// set displacement BC's
		if (BC[i][0] == -1) fem.AddFixedBC(i, DOF_X);
		if (BC[i][1] == -1) fem.AddFixedBC(i, DOF_Y);
		if (BC[i][2] == -1) fem.AddFixedBC(i, DOF_Z);
	}

	// get the material
	FEMaterial* pmat = fem.GetMaterial(0);

	// create a solid domain
	FEElasticSolidDomain* pd = new FEElasticSolidDomain(&fem);
	pd->SetMaterial(pmat);
	pd->create(1);
	m.AddDomain(pd);
	FESolidElement& el = pd->Element(0);
	el.SetType(FE_HEX8G8);
	el.m_nID = 1;
	el.SetMatID(0);
	for (i=0; i<8; ++i) el.m_node[i] = i;

	pd->InitMaterialPointData();

	// convert strain to a displacement
	double d = sqrt(2*m_strain+1) - 1;

	// Add a loadcurve
	FELoadCurve* plc = new FELoadCurve;
	plc->Add(0, 0);
	plc->Add(1, 1);
	fem.AddLoadCurve(plc);

	// Add a prescribed BC
	int nd[4] = {1, 2, 5, 6};
	FEPrescribedBC* pdc = new FEPrescribedBC(&fem);
	fem.AddPrescribedBC(pdc);
	pdc->SetDOF(DOF_X).SetLoadCurveIndex(0).SetScale(d);
	for (i = 0; i<4; ++i) pdc->AddNode(nd[i]);

	return true;
}

//-----------------------------------------------------------------------------
BEGIN_PARAMETER_LIST(FETangentSimpleShear, FEDiagnosticScenario)
	ADD_PARAMETER(m_strain, FE_PARAM_DOUBLE, "strain");
END_PARAMETER_LIST();

//-----------------------------------------------------------------------------
bool FETangentSimpleShear::Init()
{
	FEModel& fem = GetDiagnostic()->GetFEModel();

	int i;
	vec3d r[8] = {
		vec3d(0,0,0), vec3d(1,0,0), vec3d(1,1,0), vec3d(0,1,0),
		vec3d(0,0,1), vec3d(1,0,1), vec3d(1,1,1), vec3d(0,1,1)
	};

	int BC[8][3] = {
		{-1,-1,-1},{-1,-1,-1},{-1, 0,-1}, {-1, 0,-1},
		{ 0,-1,-1},{ 0,-1,-1},{ 0, 0,-1}, { 0, 0,-1}
	};

	// --- create the FE problem ---
	// create the mesh
	FEMesh& m = fem.GetMesh();
	m.CreateNodes(8);
	for (i=0; i<8; ++i)
	{
		FENode& n = m.Node(i);
		n.m_rt = n.m_r0 = r[i];
		n.m_rid = -1;

		// set displacement BC's
		if (BC[i][0] == -1) fem.AddFixedBC(i, DOF_X);
		if (BC[i][1] == -1) fem.AddFixedBC(i, DOF_Y);
		if (BC[i][2] == -1) fem.AddFixedBC(i, DOF_Z);
	}

	// get the material
	FEMaterial* pmat = fem.GetMaterial(0);

	// create a solid domain
	FEElasticSolidDomain* pd = new FEElasticSolidDomain(&fem);
	pd->SetMaterial(pmat);
	pd->create(1);
	m.AddDomain(pd);
	FESolidElement& el = pd->Element(0);
	el.SetType(FE_HEX8G8);
	el.m_nID = 1;
	el.SetMatID(0);
	for (i=0; i<8; ++i) el.m_node[i] = i;

	pd->InitMaterialPointData();

	// convert strain to a displacement
	double d = 2*m_strain;

	// Add a loadcurve
	FELoadCurve* plc = new FELoadCurve;
	plc->Add(0, 0);
	plc->Add(1, 1);
	fem.AddLoadCurve(plc);

	// Add a prescribed BC
	FEPrescribedBC* pdc = new FEPrescribedBC(&fem);
	fem.AddPrescribedBC(pdc);
	pdc->SetDOF(DOF_X).SetLoadCurveIndex(0).SetScale(d);
	int nd[4] = { 4, 5, 6, 7 };
	for (i=0; i<4; ++i) pdc->AddNode(nd[i]);

	return true;
}

//-----------------------------------------------------------------------------
// Constructor
FETangentDiagnostic::FETangentDiagnostic(FEModel& fem) : FEDiagnostic(fem)
{
	m_pscn = 0;

	// create an analysis step
	FEAnalysis* pstep = fecore_new<FEAnalysis>(FEANALYSIS_ID, "solid", &fem);

	// create a new solver
	FESolver* pnew_solver = fecore_new<FESolver>(FESOLVER_ID, "solid", &fem);
	assert(pnew_solver);
	pstep->SetFESolver(pnew_solver);

	// keep a pointer to the fem object
    fem.AddStep(pstep);
    fem.m_nStep = 0;
    fem.SetCurrentStep(pstep);
}

//-----------------------------------------------------------------------------
FEDiagnosticScenario* FETangentDiagnostic::CreateScenario(const std::string& sname)
{
	if (sname == "uni-axial"   ) return (m_pscn = new FETangentUniaxial   (this));
	if (sname == "simple shear") return (m_pscn = new FETangentSimpleShear(this));
	return 0;
}

//-----------------------------------------------------------------------------
// Initialize the diagnostic. In this function we build the FE model depending
// on the scenario.
bool FETangentDiagnostic::Init()
{
	// make sure we have a scenario
	if (m_pscn == 0) return false;

	// initialize the scenario
	if (m_pscn->Init() == false) return false;

	return FEDiagnostic::Init();
}

//-----------------------------------------------------------------------------
// Run the tangent diagnostic. After we run the FE model, we calculate 
// the element stiffness matrix and compare that to a finite difference
// of the element residual.
bool FETangentDiagnostic::Run()
{
	Logfile::MODE oldmode = felog.SetMode(Logfile::FILE_ONLY);

	// solve the problem
	FEModel& fem = GetFEModel();
	felog.SetMode(Logfile::NEVER);
	fem.Solve();
	felog.SetMode(Logfile::FILE_ONLY);

	FEMesh& mesh = fem.GetMesh();
	FEElasticSolidDomain& bd = static_cast<FEElasticSolidDomain&>(mesh.Domain(0));

	// get the one and only element
	FESolidElement& el = bd.Element(0);

	// set up the element stiffness matrix
	matrix k0(24, 24);
	k0.zero();
	bd.ElementStiffness(fem, 0, k0);

	// print the element stiffness matrix
	felog.printf("\nActual stiffness matrix:\n");
	print_matrix(k0);

	// now calculate the derivative of the residual
	matrix k1;
	deriv_residual(k1);

	// print the approximate element stiffness matrix
	felog.printf("\nApproximate stiffness matrix:\n");
	print_matrix(k1);

	// finally calculate the difference matrix
	felog.printf("\n");
	matrix kd(24, 24);
	double kmax = 0, kij;
	int i0 = -1, j0 = -1, i, j;
	for (i=0; i<24; ++i)
		for (j=0; j<24; ++j)
		{
			kd[i][j] = k0[i][j] - k1[i][j];
			kij = 100.0*fabs(kd[i][j] / k0[0][0]);
			if (kij > kmax) 
			{
				kmax = kij;
				i0 = i;
				j0 = j;
			}
		}

	// print the difference
	felog.printf("\ndifference matrix:\n");
	print_matrix(kd);

	felog.SetMode(oldmode);

	felog.printf("\nMaximum difference: %lg%% (at (%d,%d))\n", kmax, i0, j0);

	return (kmax < 1e-4);
}

//-----------------------------------------------------------------------------
// Calculate a finite difference approximation of the derivative of the
// element residual.
void FETangentDiagnostic::deriv_residual(matrix& ke)
{
	// get the solver
	FEModel& fem = GetFEModel();
	FEAnalysis* pstep = fem.GetCurrentStep();
	FESolidSolver2& solver = static_cast<FESolidSolver2&>(*pstep->GetFESolver());

	// get the mesh
	FEMesh& mesh = fem.GetMesh();

	FEElasticSolidDomain& bd = static_cast<FEElasticSolidDomain&>(mesh.Domain(0));

	// get the one and only element
	FESolidElement& el = bd.Element(0);

	// first calculate the initial residual
	vector<double> f0(24);
	zero(f0);
	bd.ElementInternalForce(el, f0);

	// now calculate the perturbed residuals
	ke.resize(24, 24);
	ke.zero();
	int i, j, nj;
	int N = mesh.Nodes();
	double dx = 1e-8;
	vector<double> f1(24);
	for (j=0; j<3*N; ++j)
	{
		FENode& node = mesh.Node(el.m_node[j/3]);
		nj = j%3;

		switch (nj)
		{
		case 0: node.m_rt.x += dx; break;
		case 1: node.m_rt.y += dx; break;
		case 2: node.m_rt.z += dx; break;
		}


		solver.UpdateStresses();

		zero(f1);
		bd.ElementInternalForce(el, f1);

		switch (nj)
		{
		case 0: node.m_rt.x -= dx; break;
		case 1: node.m_rt.y -= dx; break;
		case 2: node.m_rt.z -= dx; break;
		}

		solver.UpdateStresses();

		for (i=0; i<3*N; ++i) ke[i][j] = -(f1[i] - f0[i])/dx;
	}
}
