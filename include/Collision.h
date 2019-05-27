#include "Rect.h"
#include "Vec2d.h"

#include <algorithm>
#include <cmath>

class Collision {

public:
	// Observação: IsColliding espera ângulos em radianos!
	// Para usar graus, forneça a sua própria implementação de Rotate,
	// ou transforme os ângulos no corpo de IsColliding.
	static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
		angleOfA *= PI / 180;
		angleOfB *= PI / 180;
		Vec2d A[] = { Vec2d(a.x, a.y + a.h),
					  Vec2d(a.x + a.w, a.y + a.h),
					  Vec2d(a.x + a.w, a.y),
					  Vec2d(a.x, a.y)
		};
		Vec2d B[] = { Vec2d(b.x, b.y + b.h),
					  Vec2d(b.x + b.w, b.y + b.h),
					  Vec2d(b.x + b.w, b.y),
					  Vec2d(b.x, b.y)
		};

		for (auto& v : A) {
			v = Rotate(v - a.GetVecCentralizado(), angleOfA) + a.GetVecCentralizado();
		}

		for (auto& v : B) {
			v = Rotate(v - b.GetVecCentralizado(), angleOfB) + b.GetVecCentralizado();
		}

		Vec2d axes[] = { (A[0] - A[1]).GetNormalizado(),
			(A[1] - A[2]).GetNormalizado(),
			(B[0] - B[1]).GetNormalizado(),
			(B[1] - B[2]).GetNormalizado() };

		for (auto& axis : axes) {
			float P[4];

			for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

			float minA = *std::min_element(P, P + 4);
			float maxA = *std::max_element(P, P + 4);

			for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

			float minB = *std::min_element(P, P + 4);
			float maxB = *std::max_element(P, P + 4);

			if (maxA < minB || minA > maxB)
				return false;
		}

		return true;
	}

private:

	static inline float Mag(const Vec2d & p) {
		return std::sqrt(p.x * p.x + p.y * p.y);
	}

	static inline Vec2d Norm(Vec2d & p) {
		return p  / Mag(p);
	}

	static inline float Dot(const Vec2d & a, const Vec2d & b) {
		return a.x* b.x + a.y * b.y;
	}

	static inline Vec2d Rotate(const Vec2d & p, float angle) {
		float cs = std::cos(angle), sn = std::sin(angle);
		return Vec2d(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
	}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }
