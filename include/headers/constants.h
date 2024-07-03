#pragma once

const int SCREEN_HEIGHT             = 600;
const int SCREEN_WIDTH              = 800;

const double NEURON_RADIUS          = 50;

const double LEARNING_RATE          = 0.33f;     // too small, too big LR may cause finding BAD (local) minimum: 0.33 should be fine
const double LEARNING_PRECISION     = 0.001f;

const int MAX_TEST_COUNT            = 5000;     // reasonable max amount