#include "linear.h"
#include "base.h"
#include "quantized.h"
#include <memory>

namespace WasmEdge::Host::WASINN::MLX {
namespace mlx::core::nn {
mx::array Linear::forward(mx::array Input) {
  if (EnableBias) {
    return mx::addmm(Parameters.at("bias"), Input,
                     transpose(Parameters.at("weight")));
  }
  return matmul(Input, transpose(Parameters.at("weight")));
}

std::shared_ptr<nn::Module> Linear::toQuantized(int GroupSize, int Bits) {
  auto QuantModel = QuantizedLinear::fromLinear(
      std::dynamic_pointer_cast<Linear>(shared_from_this()), GroupSize, Bits);
  QuantModel->Name = Name;
  return QuantModel;
}

} // namespace mlx::core::nn
} // namespace WasmEdge::Host::WASINN::MLX