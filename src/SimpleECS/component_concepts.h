#pragma once

namespace fen::concepts
{
	template<class D, class B>
	concept stricly_derived = std::is_base_of_v<B, D> && !std::is_same_v<B, D>;
}
