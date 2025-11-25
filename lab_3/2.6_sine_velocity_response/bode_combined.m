function [Amplitude , Phase_rad] = fit_sine_wave(t, y, w)
    t = t(:);
    y = y(:);

    Phi = [sin(w*t) cos(w*t)];
    theta = pinv(Phi) * y;

    C1 = theta(1);
    C2 = theta(2);

    Phase_rad = atan2(C2, C1);
    Amplitude = sqrt(C1^2 + C2^2);
end

clear; clc;

%% ==============================
%  Experimental Data Setup
%  ==============================

freqs = [0.5:0.5:5, 8, 12, 16, 20];

files = cellfun(@(f) sprintf('2_6_%s.mat', strrep(num2str(f),'.','_')), ...
                num2cell(freqs), 'UniformOutput', false);

gain_v1  = zeros(length(files),1);
phase_v1 = zeros(length(files),1);
gain_v2  = zeros(length(files),1);
phase_v2 = zeros(length(files),1);

%% --- Loop over experiment files ---
for k = 1:length(files)

    data = load(files{k});

    t  = data.ScopeData_v1.time(:);
    v1 = data.ScopeData_v1.signals.values(:);
    v2 = data.ScopeData_v2.signals.values(:);

    w = 2*pi*freqs(k);

    [A1, P1] = fit_sine_wave(t, v1, w);
    [A2, P2] = fit_sine_wave(t, v2, w);

    gain_v1(k)  = A1 / 2;         % 2 V input amplitude
    gain_v2(k)  = A2 / 2;

    phase_v1(k) = rad2deg(P1);
    phase_v2(k) = rad2deg(P2);
    if phase_v1(k) > 0
        phase_v1(k) = phase_v1(k) - 360;
    end
    if phase_v2(k) > 0
        phase_v2(k) = phase_v2(k) - 360;
    end
end

%% --- Display table ---
T = table(freqs(:), gain_v1, phase_v1, gain_v2, phase_v2, ...
          'VariableNames', {'Frequency_Hz','Gain_v1','Phase_v1_deg','Gain_v2','Phase_v2_deg'});
disp(T);


%% ==============================
%  Theoretical FRF Computation
%  ==============================

m1 = 1.522e-4;
m2 = 8.17e-5;
b1 = 1/66;
b2 = 1/660;
C  = 0;
k  = 0.073014;

a1 = (m1*b2 + m2*b1 + (m1+m2)*C) / (m1*m2);
a2 = (b1*b2 + (m1+m2)*k + (b1+b2)*C) / (m1*m2);
a3 = ((b1+b2)*k) / (m1*m2);

w_theory = 2*pi*logspace(-1, 3, 1000);
s = 1i*w_theory;

num1 = (1/(m1*m2)) .* (m2*s.^2 + (b2 + C).*s + k);
num2 = (1/(m1*m2)) .* (C.*s + k);

den = s.^3 + a1*s.^2 + a2*s + a3;

G1 = num1 ./ den;
G2 = num2 ./ den;

G1_gain  = abs(G1) * 1000;                
G1_phase = unwrap(angle(G1)) * (180/pi);

G2_gain  = abs(G2) * 1000;
G2_phase = unwrap(angle(G2)) * (180/pi);


%% ==============================
%  Overlayed Bode Plots
%  ==============================

figure;

% Magnitude
subplot(2,1,1);
loglog(w_theory/(2*pi), G1_gain, 'b', 'LineWidth', 1.5); hold on;
loglog(freqs, gain_v1*1000, 'bo', 'MarkerSize', 6);            % experimental

loglog(w_theory/(2*pi), G2_gain, 'r', 'LineWidth', 1.5);
loglog(freqs, gain_v2*1000, 'ro', 'MarkerSize', 6);            % experimental

grid on;
ylabel('Gain (mm/s per V)');
title('Theoretical and Experimental Frequency Response');
legend('G1 theory','G1 exp','G2 theory','G2 exp');

% Phase
subplot(2,1,2);
semilogx(w_theory/(2*pi), G1_phase, 'b', 'LineWidth', 1.5); hold on;
semilogx(freqs, phase_v1, 'bo', 'MarkerSize', 6);

semilogx(w_theory/(2*pi), G2_phase, 'r', 'LineWidth', 1.5);
semilogx(freqs, phase_v2, 'ro', 'MarkerSize', 6);

grid on;
xlabel('Frequency (Hz)');
ylabel('Phase (deg)');
legend('G1 theory','G1 exp','G2 theory','G2 exp');
