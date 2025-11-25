%% ==============================
%  Plot 1: v1 Only (theory + exp)
%  ==============================

figure;

% --- Magnitude ---
subplot(2,1,1);
loglog(w_theory/(2*pi), G1_gain, 'b', 'LineWidth', 1.5); hold on;
loglog(freqs, gain_v1*1000, 'bo', 'MarkerSize', 6);   % experimental
grid on;
ylabel('Gain (mm/s per V)');
title('Frequency Response for v1');
legend('v1 theory','v1 exp');

% --- Phase ---
subplot(2,1,2);
semilogx(w_theory/(2*pi), G1_phase, 'b', 'LineWidth', 1.5); hold on;
semilogx(freqs, phase_v1, 'bo', 'MarkerSize', 6);
grid on;
xlabel('Frequency (Hz)');
ylabel('Phase (deg)');
legend('v1 theory','v1 exp');


%% ==============================
%  Plot 2: v2 Only (theory + exp)
%  ==============================

figure;

% --- Magnitude ---
subplot(2,1,1);
loglog(w_theory/(2*pi), G2_gain, 'r', 'LineWidth', 1.5); hold on;
loglog(freqs, gain_v2*1000, 'ro', 'MarkerSize', 6);   % experimental
grid on;
ylabel('Gain (mm/s per V)');
title('Frequency Response for v2');
legend('v2 theory','v2 exp');

% --- Phase ---
subplot(2,1,2);
semilogx(w_theory/(2*pi), G2_phase, 'r', 'LineWidth', 1.5); hold on;
semilogx(freqs, phase_v2, 'ro', 'MarkerSize', 6);
grid on;
xlabel('Frequency (Hz)');
ylabel('Phase (deg)');
legend('v2 theory','v2 exp');
