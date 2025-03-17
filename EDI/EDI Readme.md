Let me expand on the YOLOv5 model and algorithm, and I'll add it to the README.

# Emergency Vehicle Detection and Traffic Management System

## Project Overview

This repository contains a complete traffic management solution that uses YOLOv5 object detection to identify and prioritize emergency vehicles (ambulances) in traffic. The system captures images from multiple lanes, processes them to detect vehicles, and adaptively controls traffic signals to reduce congestion and prioritize emergency response vehicles.

## Key Features

- **Emergency Vehicle Priority**: Automatically detects ambulances and gives them the highest priority
- **Adaptive Traffic Management**: Uses real-time vehicle counts to determine signal timing
- **Multi-Lane Monitoring**: Rotation mechanism covers all four lanes at an intersection
- **Statistics & Logging**: Generates detailed reports with vehicle counts and performance metrics
- **CSV Export**: Saves detection results in structured format for analysis

## System Architecture

The system consists of the following components:

1. **Image Acquisition**: Camera mounted on a servo motor captures images from all four lanes
2. **Image Processing**: YOLOv5 model running on Raspberry Pi 5 analyzes images to detect and count vehicles
3. **Traffic Density Analysis**: Custom algorithm determines lane priorities based on vehicle counts
4. **Signal Control**: Arduino Uno manages traffic lights based on the calculated priorities
5. **Real-time Monitoring**: Live visualization of detection results

## Technical Requirements

- Python 3.8+
- PyTorch
- OpenCV
- Raspberry Pi 5
- Arduino Uno
- Servo motor for camera rotation
- YOLOv5 model (custom trained)

## Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/emergency-vehicle-detection.git
cd emergency-vehicle-detection

# Install dependencies
pip install -r requirements.txt

# Download the pre-trained model
# Place gen.pt in the project root directory
```

## Usage

### Running detection on images or video

```bash
python detect.py --weights gen.pt --source /path/to/image_or_video --save-csv
```

### Running detection using webcam

```bash
python webcam.py
```

### Model validation

```bash
python val.py --weights gen.pt --data data/custom.yaml --img 640
```

## Command Line Arguments

### detect.py

```
--weights     Model path or triton URL (default: yolov5s.pt)
--source      File/dir/URL/glob/screen/0(webcam) (default: data/images)
--conf-thres  Confidence threshold (default: 0.25)
--iou-thres   NMS IoU threshold (default: 0.45)
--save-csv    Save results in CSV format
--view-img    Display results
--save-txt    Save results to *.txt
--save-conf   Save confidences in --save-txt labels
--classes     Filter by class, e.g. --classes 0, or --classes 0 2 3
```

## YOLO (You Only Look Once) Architecture

YOLO is a real-time object detection system that processes images in a single forward pass through a neural network, making it extremely fast compared to traditional detection methods. Our system uses YOLOv5, which offers significant improvements in speed and accuracy over previous versions.

### How YOLO Works

1. **Image Division**: The input image is divided into an S×S grid.
2. **Bounding Box Prediction**: For each grid cell, the model predicts:
   - B bounding boxes with confidence scores
   - Class probabilities for each box
3. **Single Forward Pass**: All predictions are made simultaneously in one network evaluation.
4. **Post-Processing**: Non-maximum suppression (NMS) is applied to remove duplicate detections.

### YOLOv5 Specific Improvements

YOLOv5 introduces several key improvements over previous YOLO versions:

- **Backbone**: CSPDarknet53 - a more efficient feature extractor
- **Neck**: PANet (Path Aggregation Network) - improves information flow between layers
- **Head**: Improved detection head with better anchor handling
- **Mosaic Augmentation**: Combines four training images into one for better training performance
- **AutoAnchor**: Automatically optimizes anchor boxes for the specific dataset

### Our Implementation

Our system uses a custom-trained YOLOv5 model specifically optimized for:

- Identifying five vehicle classes: ambulance, bus, car, motorcycle, and truck
- Special focus on emergency vehicle detection accuracy
- Optimized for performance on Raspberry Pi 5

### Training Process

We fine-tuned the YOLOv5 model on our custom dataset with the following steps:

1. **Data Collection**: Gathered and annotated thousands of images of vehicles in various traffic scenarios
2. **Data Augmentation**: Applied techniques like rotation, scaling, and color jittering to improve model robustness
3. **Transfer Learning**: Started with pre-trained weights and fine-tuned for our specific vehicle classes
4. **Hyperparameter Optimization**: Tuned learning rate, batch size, and other parameters for optimal performance
5. **Validation**: Continuously evaluated model performance on a held-out validation set

## Model Performance

Our custom trained YOLOv5 model shows significant improvement in key metrics:

| Metric | Initial Value | Final Value | Description |
|--------|--------------|-------------|-------------|
| val/box_loss | 0.1 | 0.04 | Consistent performance between training and validation sets |
| val/obj_loss | 0.055 | 0.045 | Improved object detection on the validation set |
| val/cls_loss | 0.025 | <0.01 | Reflects improved classification accuracy on unseen data |
| Metrics/precision | 0 | ~0.9 | High accuracy of positive predictions |
| Metrics/recall | 0 | ~0.9 | High proportion of true positives correctly identified |
| Metrics/mAP_0.5 | 0 | ~0.9 | Significant overall performance improvement |
| Metrics/mAP_0.5:0.95 | 0 | ~0.4 | Robust performance across varying levels of precision and recall |

## Algorithm for Traffic Management

The traffic management algorithm consists of the following steps:

1. **Vehicle Detection**: The YOLOv5 model identifies and classifies vehicles in each lane.
2. **Emergency Vehicle Detection**: Special priority is given to lanes containing emergency vehicles.
3. **Density Calculation**: The number of vehicles in each lane is used to calculate traffic density.
4. **Priority Assignment**: Lanes are assigned priorities based on:
   - Presence of emergency vehicles (highest priority)
   - Number of vehicles (higher density = higher priority)
5. **Signal Timing**: The Shortest Job First (SJF) non-preemptive algorithm determines:
   - The sequence of green signals
   - The duration of each green signal based on traffic density
6. **Signal Control**: The Arduino receives instructions and controls the traffic lights accordingly.

## Real-world Impact

The system significantly reduces traffic wait times compared to traditional fixed-timing systems:

| Lane | Traditional System (seconds) | YOLO-Based System (seconds) | Time Reduction (%) |
|------|------------------------------|------------------------------|---------------------|
| 1 | 120 | 80 | 33% |
| 2 | 150 | 90 | 40% |
| 3 | 130 | 85 | 35% |
| 4 | 160 | 100 | 37.5% |

## Methodology

1. **Image Capture**:
   - Camera rotates 90 degrees at set intervals to cover all four lanes
   - Images are sent to Raspberry Pi 5 for processing

2. **Image Processing**:
   - YOLOv5 model detects and classifies vehicles
   - Emergency vehicles (ambulances) are given special priority
   - Vehicle counts are used to calculate traffic density

3. **Traffic Light Control**:
   - Uses Shortest Job First (SJF) non-preemptive algorithm with time slicing
   - Arduino receives instructions from Raspberry Pi and controls traffic lights
   - Emergency vehicles trigger immediate green signal in their lane

## Code Structure

- `detect.py`: Main detection script for images and videos
- `val.py`: Validation script to evaluate model performance
- `webcam.py`: Real-time detection using webcam input
- `models/`: Contains YOLOv5 model architecture
- `utils/`: Helper functions and utilities
- `data/`: Dataset configurations and sample images

## Future Improvements

- Integration with city-wide traffic management systems
- Support for additional emergency vehicle types (police cars, fire trucks)
- Cloud connectivity for centralized monitoring and statistics
- Mobile app for traffic officers to monitor and override the system when needed
