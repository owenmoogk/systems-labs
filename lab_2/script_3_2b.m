s = tf('s');

m = 2.45 * 10^-4;
b = 0.0103;

G = 1 / (s*(m*s + b));

Kp = 0.967;
Kd = 8.13356 * 10^-3;
Ki = 24.297;

C_PD = Kp + Kd*s;
C_PID = Kp + Kd*s + Ki/s;

T_PD = feedback(C_PD*G, 1);
T_PID = feedback(C_PID*G, 1);

figure('Position', [100 100 800 700]);

% --- PD pole-zero map ---
subplot(2,1,1);
[p_pd, z_pd] = pzmap(T_PD);
h_z_pd = plot(real(z_pd), imag(z_pd), 'o', 'MarkerSize', 10, 'LineWidth', 2, 'Color', [0 0.3 0.9]); hold on;
h_p_pd = plot(real(p_pd), imag(p_pd), 'x', 'MarkerSize', 10, 'LineWidth', 2, 'Color', [0.85 0 0]);
grid on; axis equal;
title('Pole–Zero Map — PD Controlled System', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Real Axis'); ylabel('Imaginary Axis');
set(gca, 'FontSize', 11, 'LineWidth', 1.5);
legend([h_p_pd, h_z_pd], {'Poles', 'Zeros'}, 'Location', 'best');

% --- PID pole-zero map ---
subplot(2,1,2);
[p_pid, z_pid] = pzmap(T_PID);
h_z_pid = plot(real(z_pid), imag(z_pid), 'o', 'MarkerSize', 10, 'LineWidth', 2, 'Color', [0 0.3 0.9]); hold on;
h_p_pid = plot(real(p_pid), imag(p_pid), 'x', 'MarkerSize', 10, 'LineWidth', 2, 'Color', [0.85 0 0]);
grid on; axis equal;
title('Pole–Zero Map — PID Controlled System', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Real Axis'); ylabel('Imaginary Axis');
set(gca, 'FontSize', 11, 'LineWidth', 1.5);
legend([h_p_pid, h_z_pid], {'Poles', 'Zeros'}, 'Location', 'best');

% --- Damping output ---
disp('PD-controlled system:');
damp(T_PD)

disp('PID-controlled system:');
damp(T_PID)
