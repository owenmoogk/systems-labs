% Load the data
data = load('2_1b.mat');  % assumes it contains 'tout', 'vout', 'vin'

% Extract signals
t = data.t;
y = data.x_out;  % system output
r = data.x_r;   % reference input

% Select indices for 0.2s to 0.6s
idx = t >= 0.2 & t <= 0.5;

% Compute error
error = r(idx) - y(idx);

% Compute average error
avg_error = mean(error);

% Display result
fprintf('Average error between 0.2s and 0.6s: %.4f\n', avg_error);
