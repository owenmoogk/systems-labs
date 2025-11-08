data1 = load('2_1b.mat');
data2 = load('2_2a.mat');

err1 = data1.x_out - data1.x_r;
err2 = data2.x_out - data2.x_r;

figure;

subplot(3,1,[1 2]);
plot(data1.time, data1.x_r, 'Color', [0.6 0.6 0.6], 'LineWidth', 1); hold on;
plot(data1.time, data1.x_out, 'b', 'LineWidth', 1.2);
plot(data2.time, data2.x_out, 'r--', 'LineWidth', 1.2);
title('System Response Comparison');
xlabel('Time (s)');
ylabel('Position (mm)');
legend('Reference (x\_r)', '2\_1b (x\_out)', '2\_2a (x\_out)');
grid on;

subplot(3,1,3);
plot(data1.time, err1, 'b', 'LineWidth', 1.2); hold on;
plot(data2.time, err2, 'r--', 'LineWidth', 1.2);
title('System Error (desired - actual)');
xlabel('Time (s)');
ylabel('Error');
legend('2\_1b Error', '2\_2a Error');
grid on;
