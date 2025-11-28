clc; close all;

wd  = 34.59;          
wn  = 32.086348;      
zeta = 0.359028;      

k   = 0.073014;
m1  = 1.522e-4;
m2  = 8.17e-5;
mT  = 2.34e-4;        

b1  = 1/66;

b2  = 1/660;
bt  = 1/60;           
d1  = 10/11;
d2  = 1/11;
dt  = 1;              % not used
C   = 0;
p   = 71.063;         % not used

a1 = (m1*b2 + m2*b1 + (m1+m2)*C) / (m1*m2);
a2 = (b1*b2 + (b1+b2)*C + (m1+m2)*k) / (m1*m2);
a3 = (b1+b2)*k / (m1*m2);

s  = tf('s');

G2 = 1/(m1*m2) * (C*s + k) / (s * (s^3 + a1*s^2 + a2*s + a3));

[Wn, Zeta] = damp(G2);
wn_out   = Wn(3);
zeta_out = Zeta(3);

sisotool(G2)