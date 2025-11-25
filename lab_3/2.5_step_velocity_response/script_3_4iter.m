clear; clc;


omega_d = 34.588935;
m1 = 1.522e-4;
m2 = 8.17e-5;
b1 = 1/66;
b2 = 1/660;
C  = 0;

zeta = 0.02;          % Start between 0.01–0.20
tol = 1e-4;           % Convergence tolerance
diff = 1;             % Large initial difference

while diff > tol

    omega_n = omega_d / sqrt(1 - zeta^2);
    k = (m1*m2*omega_n^2)/(m1 + m2);

    a1 = (m1*b2 + m2*b1 + (m1+m2)*C)/(m1*m2);
    a2 = (b1*b2 + (m1+m2)*k + (b1+b2)*C)/(m1*m2);
    a3 = ((b1+b2)*k)/(m1*m2);

    den = [1 a1 a2 a3];
    sys = tf(1, den);

    [wn, zetas, p] = damp(sys);

    % find complex poles
    idx = find(imag(p) ~= 0, 1);

    if isempty(idx)
        warning('No complex poles found — system is overdamped. Iteration stops.');
        break
    end

    new_zeta = zetas(idx);

    diff = abs(new_zeta - zeta);
    zeta = new_zeta;
    omega_n = omega_d / sqrt(1 - zeta^2);


end

fprintf("Converged results:\n");
fprintf("wn       = %.6f\n", omega_n);
fprintf("zeta     = %.6f\n", zeta);
fprintf("k        = %.6f N/m\n",k);