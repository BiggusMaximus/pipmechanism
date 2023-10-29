class KalmanFilter {
    public:
        KalmanFilter(double initialEstimate, double initialEstimateError, double processNoise, double measurementNoise) {
            x = initialEstimate;
            P = initialEstimateError;
            this->processNoise = processNoise;
            this->measurementNoise = measurementNoise;
        }

        void predict() {
            x_hat = x;
            P_hat = P + processNoise;
        }

        void update(double measurement) {
            K = P_hat / (P_hat + measurementNoise);
            x = x_hat + K * (measurement - x_hat);
            P = (1 - K) * P_hat;
        }

        double getState() {
            return x;
        }

    private:
        double x;  // State estimate
        double P;  // Error covariance
        double processNoise;     // Process noise covariance
        double measurementNoise; // Measurement noise covariance

        double x_hat;  // Predicted state estimate
        double P_hat;  // Predicted error covariance
        double K;     // Kalman gain
};