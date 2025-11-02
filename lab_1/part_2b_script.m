clear; clc;

% --- Parameters ---
A = 5;             % Input amplitude
f = 0.5;           % Frequency (Hz)
files = dir('4_2A_*.mat');   % All relevant files

% --- Generate input signal (square wave) ---
t_input = linspace(0, 8, 8001);
u_ref = A * square(2 * pi * f * t_input + pi)';   % Reference input

for k = 1:length(files)
    % Load data
    load(files(k).name, 'xout', 'tout');
    
    % Parse Kp from filename, e.g. 4_2A_0_5 → Kp = 0.5
    tokens = regexp(files(k).name, '4_2A_(\d+)_(\d+)', 'tokens');
    if ~isempty(tokens)
        kp_str = strrep(strjoin(tokens{1}, '.'), '_', '.');
        Kp = str2double(kp_str);
    else
        Kp = NaN;
    end
    
    % Ensure input and output time bases align
    % (if tout is not exactly same as t_input)
    if length(tout) ~= length(u_ref)
        u_interp = interp1(t_input, u_ref, tout, 'linear', 'extrap');
    else
        u_interp = u_ref;
    end

    % Compute control signal: (input - output) * Kp
    control_signal = (u_interp - xout) * Kp;

    % --- Create figure ---
    figure('Name', sprintf('Kp = %.2f', Kp));
    
    % --- Top subplot: output vs input ---
    subplot(2,1,1);
    hold on; grid on;
    plot(t_input, u_ref, 'k--', 'LineWidth', 1.5, 'DisplayName', 'Input (square wave)');
    plot(tout, xout, 'b', 'LineWidth', 1.5, 'DisplayName', 'Output');
    title(sprintf('System Response (K_p = %.2f)', Kp));
    xlabel('Time (s)');
    ylabel('Position');
    legend('show', 'Location', 'best');
    hold off;

    % --- Bottom subplot: control signal ---
    subplot(2,1,2);
    plot(tout, control_signal, 'r', 'LineWidth', 1.5);
    grid on;
    title('Control Signal (u_c = K_p × (Input - Output))');
    xlabel('Time (s)');
    ylabel('Control Signal (mm)');
end
