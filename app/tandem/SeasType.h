#ifndef SEASTYPE_20210420_H
#define SEASTYPE_20210420_H

namespace tndm {

enum class SeasMode {
    Unknown = 0,
    QuasiDynamic = 1,
    QuasiDynamicDiscreteGreen = 2,
    FullyDynamic = 3
};
enum class SeasType { Unknown = 0, Poisson = 1, Elasticity = 2 };

} // namespace tndm

#endif // SEASTYPE_20210420_H
