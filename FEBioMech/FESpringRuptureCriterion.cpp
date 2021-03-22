/*This file is part of the FEBio source code and is licensed under the MIT license
listed below.

See Copyright-FEBio.txt for details.

Copyright (c) 2020 University of Utah, The Trustees of Columbia University in
the City of New York, and others.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "stdafx.h"
#include "FESpringRuptureCriterion.h"
#include "FEDiscreteElasticMaterial.h"
#include <FECore/FEElement.h>

BEGIN_FECORE_CLASS(FESpringRuptureCriterion, FEMeshAdaptorCriterion)
	ADD_PARAMETER(m_maxForce  , "max_force");
	ADD_PARAMETER(m_maxStretch, "max_stretch");
END_FECORE_CLASS();

FESpringRuptureCriterion::FESpringRuptureCriterion(FEModel* fem) : FEMeshAdaptorCriterion(fem)
{
	m_maxForce = 0.0;
	m_maxStretch = 0.0;

	// set sort on by default
	SetSort(true);
}

bool FESpringRuptureCriterion::Check(FEElement& el, double& elemVal)
{
	if (el.isActive() == false) return false;

	bool bselect = false;
	int nint = el.GaussPoints();
	elemVal = 0;
	for (int n = 0; n < nint; ++n)
	{
		FEMaterialPoint* mp = el.GetMaterialPoint(n);
		FEDiscreteElasticMaterialPoint* ep = mp->ExtractData<FEDiscreteElasticMaterialPoint>();
		if (ep)
		{
			vec3d& Ft = ep->m_Ft;
			double F = ep->m_drt*Ft;
			double L0 = ep->m_dr0.norm();
			double Lt = ep->m_drt.norm();
			double s = Lt / L0;

			if ((m_maxForce != 0.0) && (F >= m_maxForce))
			{
				bselect = true;
			}

			if ((m_maxStretch != 0.0) && (s >= m_maxStretch))
			{
				bselect = true;
			}
		}
	}

	return bselect;
}
