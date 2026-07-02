package com.abhinav.tetris.dto;

public record ErrorResponse(
        int status,
        String message
)
{
}
