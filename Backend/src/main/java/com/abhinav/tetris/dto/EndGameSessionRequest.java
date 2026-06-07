package com.abhinav.tetris.dto;

import java.time.Duration;

public record EndGameSessionRequest(
        Long linesCleared,
        Long score

) { }
