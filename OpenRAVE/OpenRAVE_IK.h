#ifndef OPENRAVE_IK_H
#define OPENRAVE_IK_H
/// autogenerated analytical inverse kinematics code from ikfast program part of OpenRAVE
/// \author Rosen Diankov
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// ikfast version 34 generated on 2011-02-21 19:49:44.129490
/// To compile with gcc:
///     gcc -lstdc++ ik.cpp
/// To compile without any main function as a shared object:
///     gcc -fPIC -lstdc++ -DIKFAST_NO_MAIN -shared -Wl,-soname,ik.so -o ik.so ik.cpp
#ifdef BOOST_ASSERT
#define IKFAST_ASSERT BOOST_ASSERT
#else

#include <stdexcept>
#include <sstream>
#include <vector>

#ifdef _MSC_VER
#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif
#endif

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __func__
#endif

#define IKFAST_ASSERT(b) { if( !(b) ) { std::stringstream ss; ss << "ikfast exception: " << __FILE__ << ":" << __LINE__ << ": " <<__PRETTY_FUNCTION__ << ": Assertion '" << #b << "' failed"; throw std::runtime_error(ss.str()); } }
#endif

#if defined(_MSC_VER)
#define IKFAST_ALIGNED16(x) __declspec(align(16)) x
#else
#define IKFAST_ALIGNED16(x) x __attribute((aligned(16)))
#endif

#define IK2PI  6.28318530717959
#define IKPI  3.14159265358979
#define IKPI_2  1.57079632679490

#ifdef _MSC_VER
#ifndef isnan
#define isnan _isnan
#endif
#endif							 // _MSC_VER

// defined when creating a shared object/dll
#ifdef IKFAST_CLIBRARY
#ifdef _MSC_VER
#define IKFAST_API extern "C" __declspec(dllexport)
#else
#define IKFAST_API extern "C"
#endif
#else
#define IKFAST_API
#endif

typedef double IKReal;
class IKSolution
{
	public:
		/// Gets a solution given its free parameters
		/// \param pfree The free parameters required, range is in [-pi,pi]
		void GetSolution(IKReal* psolution, const IKReal* pfree) const
		{
			for(size_t i = 0; i < basesol.size(); ++i)
			{
				if( basesol[i].freeind < 0 )
					psolution[i] = basesol[i].foffset;
				else
				{
					IKFAST_ASSERT(pfree != NULL);
					psolution[i] = pfree[basesol[i].freeind]*basesol[i].fmul + basesol[i].foffset;
					if( psolution[i] > IKPI )
					{
						psolution[i] -= IK2PI;
					}
					else if( psolution[i] < -IKPI )
					{
						psolution[i] += IK2PI;
					}
				}
			}
		}

		/// Gets the free parameters the solution requires to be set before a full solution can be returned
		/// \return vector of indices indicating the free parameters
		const std::vector<int>& GetFree() const { return vfree; }

		struct VARIABLE
		{
			VARIABLE() : freeind(-1), fmul(0), foffset(0) {}
			VARIABLE(int freeind, IKReal fmul, IKReal foffset) : freeind(freeind), fmul(fmul), foffset(foffset) {}
			int freeind;
			IKReal fmul, foffset;///< joint value is fmul*sol[freeind]+foffset
		};

								 ///< solution and their offsets if joints are mimiced
		std::vector<VARIABLE> basesol;
		std::vector<int> vfree;
};
#endif
