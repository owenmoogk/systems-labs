clear; clc;

% --- Parameters ---
A = 5;             % Input amplitude
f = 0.5;           % Frequency (Hz)
Kv = 96.72;        % System gain
tau = 0.0237;      % Time constant (s)
files = dir('4_2A_*.mat');

% --- Generate input signal (square wave that starts low) ---
t_input = linspace(0, 8, 8001);
u_ref = A * square(2 * pi * f * t_input + pi)';  % start low

for k = 1:length(files)
    % Load data
    S = load(files(k).name, 'xout', 'tout');
    xout = S.xout(:);
    tout = S.tout(:);

    % Parse Kp from filename
    tokens = regexp(files(k).name, '4_2A_(\d+)_(\d+)', 'tokens');
    if ~isempty(tokens)
        kp_str = strjoin(tokens{1}, '.');
        Kp = str2double(kp_str);
    else
        Kp = NaN;
    end

    % Interpolate input
    if numel(tout) ~= numel(t_input)
        u_interp = interp1(t_input, u_ref, tout, 'linear', 'extrap');
    else
        u_interp = u_ref;
    end

    % --- Closed-loop theoretical response ---
    num = Kp * Kv / tau;
    den = [1, 1/tau, Kp * Kv/tau];
    sys_cl = tf(num, den);

    % Simulate closed-loop response to the same input
    y_theoretical = lsim(sys_cl, u_interp, tout);

    % --- Compute control signals ---
    control_exp = Kp * (u_interp - xout);       % Experimental control signal
    control_theoretical = Kp * (u_interp - y_theoretical); % Theoretical control signal

    % --- Create figure ---
    f = figure('Name', sprintf('Kp = %.2f', Kp), 'NumberTitle', 'off', ...
               'Visible', 'off');

    % --- Top: system responses ---
    subplot(2,1,1);
    plot(tout, u_interp, 'k--', 'LineWidth', 1.2); hold on;
    plot(tout, xout, 'b', 'LineWidth', 1.2);
    plot(tout, y_theoretical, 'r', 'LineWidth', 1.2);
    title(sprintf('System Response (K_p = %.2f)', Kp));
    xlabel('Time (s)');
    ylabel('Amplitude');
    legend({'Input (square wave)', 'Experimental Output', 'Theoretical Output'}, ...
           'Location', 'best');
    grid on;

    % --- Bottom: control signals ---
    subplot(2,1,2);
    plot(tout, control_exp, 'b', 'LineWidth', 1.2); hold on;          % blue
    plot(tout, control_theoretical, 'r', 'LineWidth', 1.2);           % red solid
    title('Control Signal (u_c = K_p × (Input - Output))');
    xlabel('Time (s)');
    ylabel('Control Signal (u_c)');
    legend({'Experimental', 'Theoretical'}, 'Location', 'best');
    grid on;

    % Show figure after rendering
    set(f, 'Visible', 'on');
    drawnow limitrate;
end
