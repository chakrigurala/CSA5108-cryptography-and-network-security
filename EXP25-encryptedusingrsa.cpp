#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

void commonModulusAttack(mpz_t c1, mpz_t c2, mpz_t n, mpz_t e, mpz_t result) {
    mpz_t gcd_result;
    mpz_init(gcd_result);

    // Calculate gcd(c1^e - c2^e, n)
    mpz_powm(result, c1, e, n);
    mpz_powm(gcd_result, c2, e, n);
    mpz_sub(result, result, gcd_result);
    mpz_gcd(result, result, n);

    mpz_clear(gcd_result);
}

int main() {
    mpz_t n, e, c1, c2, result;
    mpz_inits(n, e, c1, c2, result, NULL);

    // Initialize values (replace these with your actual values)
    mpz_set_str(n, "9449868410449", 10);  // n = p * q
    mpz_set_str(e, "65537", 10);          // public exponent
    mpz_set_str(c1, "123456789", 10);      // ciphertext 1
    mpz_set_str(c2, "987654321", 10);      // ciphertext 2

    commonModulusAttack(c1, c2, n, e, result);

    gmp_printf("Common factor: %Zd\n", result);

    mpz_clears(n, e, c1, c2, result, NULL);

    return 0;
}

