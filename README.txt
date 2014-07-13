+================================================
+ RSA encryption example
+================================================
p = 61, q = 53, e = 17

Compute the modulus as n = p * q

  C:\mul 61 53
  3233 = 61 * 53

Compute the totient of the product as (p-1) * (q-1)

  C:\totient 3233
  totient (3233) = 3120

Compute d, the modular multiplicative inverse of 3120

d = (e ^ -1) % n

  C:\invmod 17 3120
  2753 = 17 ^ -1 % 3120
  
Public key is (n=3233, e=17)
Private key is (n=3233, d=2753)

To encrypt plaintext message 65 using public key.
  
c = m ^ e % n

  C:\modexp 65 17 3233
  2790 = 65 ^ 17 % 3233
  
To decrypt ciphertext 2790 using private key.

m = c ^ d % m

  C:\modexp 2790 17 2753
  65 = 2790 ^ 2753 % 3233
  
+================================================
+ Diffie Hellman Merkle key exchange example
+================================================

p = 23, g = 5 (primitive root of p)

Alice chooses a secret integer x = 6 and computes A using p and g:
    
A = g ^ x % p

    C:\modexp 5 6 23
    8 = 5 ^ 6 % 23
 
The value of A is sent to Bob
Bob chooses a secret integer y = 15 and computes B using p and g:
      
B = g ^ y % p

    C:\modexp 5 15 23
    19 = 5 ^ 15 % 23
  
The value of B is sent to Alice
Next, both Bob and Alice compute a session key using exchanged values.

Alice computes

s = B ^ x % p
    
    C:\modexp 19 6 23
    2 = 19 ^ 6 % 23
    
Bob computes
  
s = A ^ y % p
  
    C:\modexp 8 15 23
    2 = 8 ^ 15 % 23
    
The value of 2 is the session key which can then be used with KDF
to create symmetric encryption key.

+================================================
+ ElGamal Encryption example
+================================================

Alice chooses prime p and generator g as public keys.

p = 139, g = 3
    
Alice chooses a secret integer x = 12 and computes using p and g, Y.
  
Y = g ^ x % p
  
  C:\modexp 3 12 139
  44 = 3 ^ 12 % 139
    
Alice publishes Y, g and p
  
To send m=100 to Alice, Bob chooses random k=52
  
s = Y ^ k % p
  
  C:\modexp 44 52 139
  112 = 44 ^ 52 % 139
  
c1 = g ^ k % p
  
  C:\modexp 3 52 139
  38 = 3 ^ 52 % 139
  
c2 = m * s % p
  
  C:\mulmod 100 112 139
  80 = 100 * 112 % 139
  
Alice does the following to decrypt (c1, c2)
Generate the shared secret, s

s = c1 ^ x % p
  
  C:\modexp 38 12 139
  112 = 38 ^ 12 % 139
  
Calculate modular multiplicative inverse of s mod p
 
(s ^ -1) = s ^ -1 % p
  
  C:\invmod 112 139
  36 = (112 ^ -1) % 139
  
Multiply previous operation with c2 mod p to recover plaintext

m = (s ^ -1) * c2) % p

  C:\mulmod 36 80 139
  100 = 36 * 80 % 139
  
* Each user has a private key x
* Each user has three public keys:  p, g and public Y = gx mod p
* Security is based on the difficulty of DLP
* Secure key size > 1024 bits ( today even 2048 bits)
* Elgamal is quite slow, it is used mainly for key authentication protocols
* Now widely used, but Elliptic Curve variant is increasingly popular


+================================================
+ STS (Station-To-Station protocol) key agreement
+================================================

    Alice generates a random number x and computes and sends the exponential gx to Bob.
    Bob generates a random number y and computes the exponential gy.
    Bob computes the shared secret key K = (gx)y.
    Bob concatenates the exponentials (gy, gx) (order is important), signs them using his asymmetric key B, and then encrypts the signature with K. He sends the ciphertext along with his own exponential gy to Alice.
    Alice computes the shared secret key K = (gy)x.
    Alice decrypts and verifies Bob's signature.
    Alice concatenates the exponentials (gx, gy) (order is important), signs them using her asymmetric key A, and then encrypts the signature with K. She sends the ciphertext to Bob.
    Bob decrypts and verifies Alice's signature.

    