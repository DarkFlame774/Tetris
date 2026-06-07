package com.abhinav.tetris.dto;

import jakarta.validation.constraints.NotBlank;

public record StartGameSessionResponse(
        Long sessionId
) { }
