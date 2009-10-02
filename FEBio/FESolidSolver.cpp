#include "stdafx.h"
#include "FESolidSolver.h"
#include "fem.h"

///////////////////////////////////////////////////////////////////////////////
// FESolidSolver Construction/Destruction
//

FESolidSolver::FESolidSolver(FEM& fem) : FESolver(fem)
{
	// default values
	m_Rtol = 1e10;
	m_Dtol = 0.001;
	m_Etol = 0.01;
	m_LStol = 0.9;
	m_LSmin = 0.01;
	m_LSiter = 5;
	m_maxups = 10;
	m_maxref = 15;
	m_cmax   = 1e5;

	m_niter = 0;
}

//-----------------------------------------------------------------------------
//! Save data to dump file

void FESolidSolver::Serialize(Archive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_Dtol << m_Etol << m_Rtol << m_LSmin << m_LStol << m_LSiter;
		ar << m_maxups;
		ar << m_maxref;
		ar << m_cmax;

		ar << m_nrhs;
		ar << m_niter;
		ar << m_nref;
		ar << m_nups;
		ar << m_naug;
	}
	else
	{
		ar >> m_Dtol >> m_Etol >> m_Rtol >> m_LSmin >> m_LStol >> m_LSiter;
		ar >> m_maxups;
		ar >> m_maxref;
		ar >> m_cmax;

		ar >> m_nrhs;
		ar >> m_niter;
		ar >> m_nref;
		ar >> m_nups;
		ar >> m_naug;
	}
}

