CREATE TABLE pipmechanism (
    id INT AUTO_INCREMENT PRIMARY KEY,
    voltage FLOAT,
    current FLOAT,
    power FLOAT,
    time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
