#ifndef DG_20200615_H
#define DG_20200615_H

#include "geometry/Curvilinear.h"
#include "mesh/LocalSimplexMesh.h"
#include "quadrules/AutoRule.h"
#include "tensor/Managed.h"
#include "tensor/Tensor.h"

#include <mneme/storage.hpp>
#include <mneme/view.hpp>

#include <cstddef>
#include <vector>

namespace tndm {

template <std::size_t D> class DG {
public:
    DG(LocalSimplexMesh<D> const& mesh, Curvilinear<D>& cl, unsigned degree, unsigned minQuadOrder);
    virtual ~DG() = default;

    std::size_t numElements() const { return vol.size(); }
    std::size_t numFacets() const { return fctInfo.size(); }

protected:
    void facetPrecompute(LocalSimplexMesh<D> const& mesh, Curvilinear<D>& cl);
    void volumePrecompute(LocalSimplexMesh<D> const& mesh, Curvilinear<D>& cl);

    SimplexQuadratureRule<D - 1u> fctRule;
    SimplexQuadratureRule<D> volRule;

    Managed<Tensor<double, 3u>> Dxi;

    Managed<Matrix<double>> E;
    Managed<Tensor<double, 3u>> gradE;
    std::vector<Managed<Matrix<double>>> fctE;
    std::vector<Managed<Tensor<double, 3u>>> fctGradE;

    struct AbsDetJ {
        using type = double;
    };
    struct JInvT {
        using type = std::array<double, D * D>;
    };
    struct Normal {
        using type = std::array<double, D>;
    };

    struct FacetInfo {
        std::array<std::size_t, 2> up;
        std::array<std::size_t, 2> localNo;
    };
    std::vector<FacetInfo> fctInfo;

    mneme::MultiStorage<mneme::DataLayout::SoA, JInvT, Normal> fctStore;
    mneme::StridedView<decltype(fctStore)> fct;

    mneme::MultiStorage<mneme::DataLayout::SoA, AbsDetJ, JInvT> volStore;
    mneme::StridedView<decltype(volStore)> vol;
};

} // namespace tndm

#endif // DG_20200615_H